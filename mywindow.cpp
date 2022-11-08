#include "mywindow.h"
#include "ui_mywindow.h"
#include <iostream>
using namespace std;

MyWindow::MyWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("子窗口");
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
    qDebug() << "start iterator 1: ";
    while(i.hasNext()) {
//        QString num = i.;
//        if(num == "+") {
//            i.remove();
//        }
//        i.next();
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
    qDebug() << "start iterator 2: ";
    while(j != list.constEnd()) {
        qDebug() << *j;
        j++;
    }

    /*
     * 遍历方式3：
     * foreach宏；
     * 第一个参数是遍历元素的指针，最好定义在外面
     * 第二个参数是容器
     */
    qDebug() << "start iterator 3: ";
    foreach (QString s, list) {
        qDebug() << s;
    }

    // TODO: 遍历1删除-，遍历2删除+，遍历三输出结果
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

