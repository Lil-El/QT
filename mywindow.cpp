#include "mywindow.h"
#include "ui_mywindow.h"
#include <iostream>
#include <QDateTime>
#include <QModelIndex>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
using namespace std;

MyWindow::MyWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("子窗口");

    // table设置
    ui->tableWidget->setColumnCount(2);
    QStringList header;
    header << "Key" << "Val";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setColumnWidth(0, 140);
    ui->tableWidget->setColumnWidth(1, 60);

    // 设置tree
    ui->treeWidget->setColumnCount(2);
    QStringList headers;
    headers << "Key" << "Val";
    ui->treeWidget->setHeaderLabels(headers);
    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget, QStringList("ROOT"));
    QTreeWidgetItem *root2 = new QTreeWidgetItem(ui->treeWidget, QStringList("NUMS"));
    QTreeWidgetItem *leaf = new QTreeWidgetItem(root, QStringList("Leaf 1"));
    root->addChild(leaf);
    QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
    leaf2->setCheckState(0, Qt::Checked);
    root->addChild(leaf2);
    QList<QTreeWidgetItem *> rootList;
    rootList << root << root2;
    ui->treeWidget->insertTopLevelItems(0, rootList);

    // Dir
    this->initDirModel();

    // QSortFilterProxyModel：正则过滤-代理model
    modelProxy = new QSortFilterProxyModel(this);
    modelProxy->setSourceModel(model);
    modelProxy->setFilterKeyColumn(0);

    // tableModel/tableView
   QMap<QString, double> data;
   data["NOK"] = 1.0;
   data["NZD"] = 2.0;
   data["SEK"] = 3.0;
   CurrencyModel *currencyModel = new CurrencyModel();
   currencyModel->setCurrencyMap(data);
   ui->tableView->setModel(currencyModel);

   // 自定义委托-Delegate；相对于其他的就是多一行setItemDelegate，其他一样
   QList<Track> tracks;
   Track t1("Mino1", 200);
   Track t2("Song 2", 150);
   Track t3("Song 3", 120);
   Track t4("Song 4", 210);
   tracks << t1 << t2 << t3 << t4;
   ui->tableWidget2->setColumnCount(2);
   ui->tableWidget2->setRowCount(tracks.count());
   ui->tableWidget2->setItemDelegate(new TrackDelegate(1));
   ui->tableWidget2->setHorizontalHeaderLabels(QStringList() << "Track" << "Duration");
   for (int row = 0; row < tracks.count(); ++row) {
       Track track = tracks.at(row);

       QTableWidgetItem *item0 = new QTableWidgetItem(track.title);
       ui->tableWidget2->setItem(row, 0, item0);

       QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(track.duration));
       item1->setTextAlignment(Qt::AlignRight);
       ui->tableWidget2->setItem(row, 1, item1);
   }
}

MyWindow::~MyWindow() {
    delete ui;
}

void MyWindow::on_spinBox_valueChanged(int val)
{
    ui->horizontalSlider->setValue(val);
}

void MyWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->spinBox->setValue(position);
}


void MyWindow::on_addButton_clicked()
{
    /*
     *
     * 我们可以使用标准 C++的 STL，也可以使用 Qt 的容器类。
     * Qt 容器类的好处在于，它提供了平台无关的行为，以及隐式数据共享技术。
     * 所谓平台无关，即 Qt 容器类不因编译器的不同而具有不同的实现；
     * 所谓“隐式数据共享”，也可以称作“写时复制 copy on write”，这种技术允许在容器类中使用传值参数，而不会发生额外的性能损失。
     *
     * 和QVector类似的有：QList->QStringList、QLinkedList、QStack、QQueue
     * Linker是链表，插入、删除很快，随机读取很慢
     * Vector是读取快一些
     *
     * Qt 容器类提供了两种遍历器：Java 风格的和 STL 风格的。
     * 对于每个容器类，都有相对应的遍历器：只读、读写遍历器。
     * 只读遍历器有QVectorIterator，QLinkedListIterator和 QListIterator三种；
     * 读写遍历器同样也有三种，即 QMutableVectorIterator，QMutableLinkedListIterator和 QMutableListIterator。
     *
     * 模板类中的占位符T，可以使基本数据类型，比如 int，double 等，也可以指针类型，可以是类类型。
     * 如果是类类型的话，必须提供默认构造函数，拷贝构造函数和赋值操作符。
     * Qt 的内置类中的 QByteArray，QDateTime，QRegExp，QString和QVariant是满足这些条件的。
     * 但是，QObject 的子类并不符合这些条件，因为它们通常缺少拷贝构造函数和赋值操作符。
     * 不过这并不是一个问题，因为我们可以存储 QObject 的指针，而不是直接存储值。
     *
     * QList<QVector<int> > list; 这个空格为了防止编译器把两个>解析为>>操作符。
     */

    /*
     * 在C++中如果函数返回值是一个数组或相关的类，那么会进行拷贝构造函数的调用，影响性能；如：QList fnName(QList list);
     * 在C++中就会改成：void fnName(QList &list);
     * 在Qt中容器类和QByteArray, QBrush, QFont, QImage, QPixmap 和 QString等都使用了隐式数据共享，可以规避上述的问题。
     *
     * 正确使用隐式数据共享，我们需要建立一个良好的编程习惯。
     * 这其中之一就是，对 list 或者 vector 使用 at()函数而不是[]操作符进行只读访问。
     * 原因是[]操作符既可以是左值又可以是右值，这让 Qt 容器很难判断到底是左值还是右值，而 at()函数是不能作为左值的，因此可以进行隐式数据共享。
     * 另外一点是，对于 begin()，end()以及其他一些非 const 容器，在数据改变时 Qt 会进行深复制。
     * 为了避免这一点，要尽可能使用 const_iterator, constBegin()和 constEnd().
     */

    /*
     * int转QString方式：
     * 1. 使用QString("%n").arg(1);
     * 2. 使用QString:number();
     */
    QString num = QString::number(ui->spinBox->value(), 10);
    ui->list->addItem(num);

    // QVector操作
    this->list << "-";
    this->list.append(num);
    this->list << "+";

    /*
     * 遍历方式1：
     * Java风格遍历：每个i指向元素的前后；
     * 使用读写遍历器才可以进行修改remove元素；通过读写遍历器对“+”移除
     * begin()，end()以及其他一些非 const 容器，在数据改变时 Qt 会进行深复制。为了避免这一点，要尽可能使用 const_iterator, constBegin()和 constEnd().
     */
    QMutableListIterator<QString> i(list);
    while(i.hasNext()) {
        QString num = i.next();
        if(num == "+") {
            i.remove();
        }
    }

    /*
     * 遍历方式2：
     * 对应于 Java 风格的遍历器，每一个顺序容器类 C都有两个 STL 风格的遍历器：iterator和const_iterator
     * STL遍历器i指向元素；
     * 如果容器是通过一个返回容器类的函数获取的，那么在使用STL风格时，需要将返回值进行拷贝；QVector<T> list = getList(); 【需要给T实现拷贝构造函数】
     * 如果不这么做，直接getList()::iterator的话，函数返回时，返回值临时对象会销毁，并且有性能问题。
     * 所以需要先赋值，返回调用。QVector list = getList(); list::iterator i;
     * 如果容易数据庞大，这也是影响性能的。在Qt中使用了隐式数据共享，拷贝容器像指针拷贝一样快速。
     * 如果我们只进行读操作，数据是不会被复制的，只有当这些需要复制的数据需要进行写操作，这些数据才会被真正的复制，而这一切都是自动进行的，也正因为这个原因，隐式数据共享有时也被称为“写时复制”。
     */
    QVector<QString>::const_iterator j = list.constBegin();
    while(j != list.constEnd()) {
        if (*j == "-") {
            list.erase(j);
        }
        j++;
    }

    /*
     * 遍历方式3：
     * foreach宏；
     * 第一个参数是遍历元素的指针，最好定义在外面
     * 第二个参数是容器
     */
    qDebug() << "start iterator 3: ";
    // C++遍历
    for(QString s : list) {
        qDebug() << s;
    }

    // Qt遍历
    /*
     * QMap：key是唯一的， 重复会覆盖
     * QMultiMap：key可以重复，QList<QString> list = map.value(1); 使用list接收读个QString类型的value；
     * QCache<K, T>来提供缓存，QSet用于仅存储 key 的情况
     *
     * QHash<K, T>是使用散列存储的键-值对。它的接口同 QMap<K, T>几乎一样，但是它们两个的实现需求不同。
     * QHash<K, T>的查找速度比 QMap<K, T>快很多，并且它的存储是不排序的。
     * 对于 QHash<K, T>而言，K 的类型必须重载了==操作符，并且必须被全局函数 qHash()所支持，这个函数用于返回 key的散列值。
     * Qt 已经为 int、指针、QChar、QString 和 QByteArray 实现了 qHash()函数。
     *
     * QHash<K, T>会自动地为散列分配一个初始大小，并且在插入数据或者删除数据的时候改变散列的大小。
     * 我们可以使用 reserve()函数扩大散列，使用 squeeze()函数将散列缩小到最小大小(这个最小大小实际上是能够存储这些数据的最小空间)。
     * 在使用时，我们可以使用 reserve()函数将数据项扩大到我们所期望的最大值，然后插入数据，完成之后使用 squeeze()函数收缩空间。
     *
     * QHash<K, T>同样也是单值类型的，但是你可以使用 insertMulti()函数，或者是使用QMultiHash<K, T>类来为一个键插入多个值。
     * 另外，除了 QHash<K, T>，Qt 也提供了 QCache<K, T>来提供缓存，QSet用于仅存储 key 的情况。这两个类同 QHash<K, T>一样具有 K 的类型限制。
     */
    QMap<int, QString> map;
    int index = 0;
    foreach (QString s, list) {
        map.insert(index, s); // map[index] = s;
        index++;
    }

    // QMutableMapIterator mi; mi.setValue(12);
    // Java风格
    QMapIterator<int, QString> mi(map);
    while(mi.hasNext()) {
        mi.next();
        qDebug() << "key: " << mi.key() << " value: " << mi.value();
    }
    qDebug() << map.value(3, "Mino"); // 获取key=1的value，没有就输出第二个参数-默认值

    // STL风格
    foreach (int key, map.keys()) {
    }
    foreach (QString value, map.values()) {
    }

    this->addTable(num);
    this->addTree(num);
}


void MyWindow::on_saveButton_clicked()
{

}


void MyWindow::on_clearCacheButton_clicked()
{

}


void MyWindow::on_loadCacheButton_clicked()
{
}

void MyWindow::addTable(const QString &str) {
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rowCount + 1);
    QDateTime dt(QDateTime::currentDateTime());
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(dt.toString(QString("yyyy-MM-dd hh:mm:ss"))));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(str));
}

void MyWindow::addTree(const QString &str) {
    int rootCount = ui->treeWidget->topLevelItemCount();
    for (int idx = 0; idx < rootCount; ++idx) {
        QTreeWidgetItem *root = ui->treeWidget->topLevelItem(idx);
        QString rootText = root->text(0);
        if(rootText == "NUMS") {
            QStringList list;
            list << "Mino" << str;
            QTreeWidgetItem *leaf = new QTreeWidgetItem(root, list);
            root->addChild(leaf);
        }
    }
}

/*
 * QDirModel 在最新版 Qt 中已经不建议使用了。文档中说使用 QFileSystemModel 代替。
 * 由于这两者的函数几乎一样，所以就没有对代码进行修改。
 * 与QDirModel不同的是，QFileSystemModel会启动自己的线程进行文件夹的扫描，因此不会发生因扫描文件夹而导致的主线程阻塞的现象。
 * 另外，无论 QDirModel还是QFileSystemModel都会对model结果进行缓存，如果你要立即刷新结果，前者提供了refresh()函数，而后者会通知QFileSystemWatcher类。
*/
void MyWindow::initDirModel() {
    model = new QFileSystemModel();
//    排序的依据也很清楚：文件夹优先(QDir::DirsFirst)，忽略大小写(QDir::IgnoreCase)，而且是根据名字排序(QDir::Name)。更多的规则组合可以参见 API 文档了
//    model->sort();
    /*
     * MVC：model-view架构
     * 上面是QTreeWidget，基于Item
     * QTreeView，基于Model；Model可以同时传给多个View
     *
     * 在少量数据的情形下，我们不需要动用 model 这样重量级的组件。
     * Qt 为了方便起见也提供了 item view 类，分别是 QListWidget，QTableWidget 和 QTreeWidget，使用这些类可以直接对 item 进行操作。
     * 对于很大的数据，我们则需要使用 Qt 的 view 类，比如 QListView，QTabelView 和 QTreeView，同时需要提供一个 model，可以是自定义 model，也可以是 Qt 预置的model。
     * 如果数据来自数据库，那么你可以使用 QTabelView 和 QSqlTableModel 这两个类。
     */
    tree = new QTreeView();

    model->setReadOnly(false);
    model->setRootPath(QDir::currentPath()); // Qt Project debug directory

    tree->setModel(model);
    tree->header()->setStretchLastSection(true); // 分配剩余空间
    tree->header()->setSortIndicator(0, Qt::AscendingOrder); // 第一列（名称）排序 Qt::AscendingOrder/Qt::DescendingOrder
    tree->header()->setSortIndicatorShown(true); // 设置排序指示器显示

    QModelIndex index = model->index(QDir::currentPath()); // 寻找目录的index，然后展开并滚动至index的位置
    tree->expand(index);
    tree->scrollTo(index);
    tree->resizeColumnToContents(0); // 让列和目录的名称长度一样宽

    ui->dirLayout->addWidget(tree);

    connect(ui->mkdirButton, SIGNAL(clicked()), this, SLOT(on_mkdir()));
    connect(ui->rmdirButton, SIGNAL(clicked()), this, SLOT(on_rmdir()));
}

void MyWindow::on_mkdir() {
    QModelIndex index = this->tree->currentIndex();
    if (!index.isValid()) {
        qDebug() << "index is not valid.";
        return;
    }
    QString dirName = QInputDialog::getText(this, "创建", "名称");
    if (!dirName.isEmpty()) {
        if (!model->mkdir(index, dirName).isValid()) {
            QMessageBox::information(this, "About", "Failed to create the dir.");
        }
    }
}

void MyWindow::on_rmdir() {
    QModelIndex index = tree->currentIndex();
    if (!index.isValid()) {
        return;
    }
    bool ok;
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok) {
        QMessageBox::information(this, "Remove", tr("Failed to remove %1").arg(model->fileName(index)));
    }
}

void MyWindow::on_searchInput_textChanged(const QString &text)
{
    // 因为设置proxy之后，tree无法展开currentPath，所以setModel设置到这里。在不需要搜索时，设置为setModel(model)
    this->tree->setModel(modelProxy);

    QRegularExpression regexp(text);
    modelProxy->setFilterRegularExpression(regexp);
}

