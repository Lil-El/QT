#include "dnd.h"
#include "ui_dnd.h"
#include <QMimeData>
#include <QFile>
#include <QClipboard>

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

