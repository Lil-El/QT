#include "paint.h"
#include "ui_paint.h"
#include <iostream>
using namespace std;

Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);
    this->setWindowTitle("Painter");
}

Paint::~Paint()
{
    delete ui;
}
