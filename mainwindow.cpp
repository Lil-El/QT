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
    //    https://www.w3cschool.cn/learnroadqt/edlr1j3y.html 手动连接信号、槽connect
    //    cout << (ui->button_exit) << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// TODO: https://zhuanlan.zhihu.com/p/265341090
// QT内部处理connect信号和槽的连接方式：on_[name]_clicked()
void MainWindow::on_button_exit_clicked()
{
    cout << "Exit..." << endl;
}

