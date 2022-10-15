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
