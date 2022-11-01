// 参考：https://blog.csdn.net/Albert_weiku/article/details/125495569
// 对Ui::MainWindow声明
#include "mainwindow.h"
// 对Ui::MainWindow定义，在编译时会mainwindow.ui编译为ui_*.h文件
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("我的QT");
    QLabel *label = new QLabel();
    label->setText("QLabel");
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
    ui->statusBar->addWidget(label);
    ui->statusBar->setSizeGripEnabled(false);
    this->setStatusTip(tr("It's status bar."));

    QAction *qa = new QAction("我的", this); // QAction 在ui_mainwindow.h中引入
    qa->setStatusTip("我的文件");
    QKeySequence ks = QKeySequence(Qt::CTRL|Qt::Key_P);
    qa->setShortcut(ks); // setShortcut(s) => QKeySequence::Print ctrl+p, QKeySequence(tr("Ctrl+p"));
    ui->startMenu->addAction(qa);
    connect(qa, SIGNAL(triggered()), this, SLOT(custom_trigger_action()));
    ui->toolBar->addAction(qa);


    // 槽函数需要参数时，参数必须来自于信号函数的参数。
    connect(ui->button_exit, SIGNAL(clicked()), this, SLOT(custom_click_listener2()), Qt::DirectConnection);

    // 使用Lambda表达式，不可以使用SIGNAL和SLOT
    connect(ui->button_exit, &QPushButton::clicked, this, [=]{
        custom_click_listener(1);
    }, Qt::AutoConnection);

    // 使用QSignalMapper进行转发，传递参数
    sp = new QSignalMapper();
    connect(ui->button_exit, SIGNAL(clicked()), sp, SLOT(map()));
    sp->setMapping(ui->button_exit, 9);
    connect(sp, SIGNAL(mappedInt(int)), this, SLOT(custom_click_listener(int)));

    connect(this, SIGNAL(my_signal()), this, SLOT(custom_trigger_fn()));

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sp;
    delete child_window;
    if(this->timerID1) {
        cout << "kill timer: " << endl;
        killTimer(this->timerID1);
    }
    if(this->timerID2 != nullptr) {
        cout << "kill timer2: " << endl;
        killTimer(this->timerID2->timerId());
    }
}

// TODO: https://zhuanlan.zhihu.com/p/265341090
// QT内部处理connect信号和槽的连接方式：on_[name]_clicked()
void MainWindow::on_button_exit_clicked()
{
    QString qs = u8"事件：自动connect";
    qDebug() << "click button:" << ((ui->button_exit->objectName()).toStdString().data());
    // 使用toLocal8Bit()处理中文乱码
    // qstring.cpp: D:\Program_Files\Qt\6.4.0\Src\qtbase\src\corelib\text
    cout << qs.toLocal8Bit().toStdString().data() << endl;

    // 手动触发自定义信号
    emit my_signal();

    // qApp宏是QApplication的实例
    qApp->quit();
}

void MainWindow::custom_click_listener(int a) {
    cout << QString(u8"事件：有参数").toLocal8Bit().toStdString().data() << a << endl;
}
void MainWindow::custom_click_listener2() {
    cout << QString(u8"事件：无参数").toLocal8Bit().toStdString().data() << endl;
}
void MainWindow::custom_trigger_fn() {
    cout << QString(u8"trigger").toLocal8Bit().toStdString().data() << endl;
}
void MainWindow::custom_trigger_fn(const QString &qs) {
    cout << qs.toLocal8Bit().toStdString().data() << endl;
}
void MainWindow::on_button_jump_clicked() {
    if(child_window == nullptr) {
        child_window = new MyWindow; // Ui::MyWindow需要引入ui_mywindow.h，而不是mywindow.h
    }
    cout << boolalpha << (typeid(*child_window) == typeid(MyWindow)) << endl;
    child_window->show();
}
void MainWindow::timerEvent(QTimerEvent *ev) {
    if(ev->timerId() == timerID1) {
        if(isDateFlag) {
            // 不传入参数DateTime就是空的
            QDateTime dt(QDateTime::currentDateTime());
            QDate date = dt.date();
            cout << QString("今天是：").toLocal8Bit().toStdString().data() << date.year() << "/" << date.month() << endl;
            QDateTime dt1 = dt.addMonths(0);
            QString dt_s = dt1.toString(QString("yyyy-MM-dd hh:mm:ss"));
            ui->DateString->setText(dt_s);
        } else {
            killTimer(timerID1);
        }
    }
}
void MainWindow::init() {
    // 定时器使用方式1-QObject：直接QObject::startTimer，每个2000毫秒后自动调用timerEvent；
//    this->timerID1 = startTimer(1000);
    // 定时器使用方式2-QTimer: 创建timer，监听timeout信号
    timerID2 = new QTimer(this);
    timerID2->setInterval(1000); // 设置时间间隔，也可以直接start(间隔)设置间隔
    timerID2->start(); // start启动定时器 stop停止定时器 再次start可以重启
    cout << timerID2->interval() << endl;
    // timeout回调1
    timerID2->callOnTimeout([=](){
        cout << "callOnTimeout" << endl;
    });
    // timeout回调2
    connect(timerID2, &QTimer::timeout, this, [=](){
        ui->DateString_2->setText(QDateTime::currentDateTime().toString());
    });
}

void MainWindow::on_DateButton_clicked()
{
    isDateFlag = false;
}
void MainWindow::on_DateButton_2_clicked()
{
    isDateFlag_2 = !isDateFlag_2;
    if(isDateFlag_2) {
        timerID2->setInterval(3000);
        timerID2->start();
    } else {
        timerID2->stop();
    }
}
void MainWindow::custom_trigger_action() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));
    if(path.length() == 0) {
        QMessageBox::warning(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }
}

void MainWindow::on_MDialogButton_clicked()
{
    mdialog = new MDialog;
    mdialog->show();
    connect(mdialog, SIGNAL(mdOK(const QString&)), this, SLOT(custom_trigger_fn(const QString&)));
}





















