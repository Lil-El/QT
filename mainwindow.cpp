// 参考：https://blog.csdn.net/Albert_weiku/article/details/125495569
// 对Ui::MainWindow声明
#include "mainwindow.h"
// 对Ui::MainWindow定义，在编译时会mainwindow.ui编译为ui_*.h文件
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("我的QT");

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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sp;
    delete child_window;
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
void MainWindow::on_button_jump_clicked() {
    cout << "Jump: " << (child_window) << endl;
    // TODO: 有了就不重新创建了
    if(child_window) return;
    else {
        child_window = new MyWindow; // Ui::MyWindow需要引入ui_mywindow.h，而不是mywindow.h
        child_window->show();
    }
}
