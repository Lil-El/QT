// 参考：https://blog.csdn.net/Albert_weiku/article/details/125495569
// 对Ui::MainWindow声明
#include "mainwindow.h"
// 对Ui::MainWindow定义，在编译时会mainwindow.ui编译为ui_*.h文件
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

