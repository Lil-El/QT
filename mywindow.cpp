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

