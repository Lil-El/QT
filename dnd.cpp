#include "dnd.h"
#include "ui_dnd.h"
#include <QMimeData>
#include <QFile>
#include <QClipboard>
#include <QProcess>

dnd::dnd(QWidget *parent) : QWidget(parent), ui(new Ui::Dnd)
{
    ui->setupUi(this);
    setWindowTitle(tr("Drag and Drop"));

    ui->textEdit->setAcceptDrops(false);
    this->setAcceptDrops(true);
}

dnd::~dnd()
{
    delete ui;
}

void dnd::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void dnd::dropEvent(QDropEvent *event) {
    QList<QUrl> list = event->mimeData()->urls();
    if (list.isEmpty()) {
        return;
    }
    QString fileName = list.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }
    if (readFile(fileName)) {
        setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
    }
}

bool dnd::readFile(const QString &fileName) {
    QFile file(fileName);
    QTextStream stream(&file);
    QString content;
    // 只可以读取一行
//    if (file.open(QIODevice::ReadOnly)) {
//        stream >> content;
//        ui->textEdit->setText(content);
//    }

    // 读取全部
//    if (file.open(QIODevice::ReadOnly)) {
//        QByteArray byte = file.readAll();
//        ui->textEdit->setText(QString(byte));
//    }

    // 读取文字
    if (file.open(QIODevice::ReadOnly)) {
        stream.seek(0);
        while(!stream.atEnd())
        {
            content.append(stream.readLine());
        }
        ui->textEdit->setText(content);
    }

    return true;
}

void dnd::on_pushButton_clicked()
{
    QClipboard *board = QApplication::clipboard();
    board->setText("Text from Qt Application");
}


void dnd::on_pushButton_2_clicked()
{
    QClipboard *board = QApplication::clipboard();
    QString str = board->text();
    ui->textEdit->append(str);
}

// 二进制，无法正常读取
void dnd::on_pushButton_3_clicked()
{
    QFile file("file.txt");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    // Write a header with a "magic number" and a version
    out << (quint32)0x12345678;
    out << (qint32)123;

    out.setVersion(QDataStream::Qt_6_4);
}


void dnd::on_pushButton_4_clicked()
{
    QFile file("file.bat");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "echo Mino吖.";

    // stream.setCodec("UTF-8"); 默认使用系统本地编码，也可以使用setCodec设置新的编码
}

// QProcess::readAll() 函数可以读出程序输出内容。我们使用这个函数将所有的输出获取之后，由于它的返回结果是 QByteArray 类型，所以再转换成 QString 显示出来。
// 另外注意一点，中文本 Windows 使用的是 GBK 编码，而 Qt 使用的是 Unicode 编码，因此需要做一下转换，否则是会出现乱码的，大家可以尝试一下。
// QProcess 可以实现进程过程的监听，或者是令Qt 程序等待这个进程结束后再继续执行的函数。
void dnd::on_pushButton_5_clicked()
{
    QProcess *p = new QProcess(this);
    p->start("cmd.exe", QStringList() << "/c" << "dir"); // 第二个参数是传给ext或bat的参数
    connect(p, SIGNAL(finished(int)), this, SLOT(readResult(int)));
}

void dnd::readResult(int exitCode)
{
    qDebug() << exitCode;
}
