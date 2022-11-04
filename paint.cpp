#include "paint.h"
#include "ui_paint.h"
#include <iostream>
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
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

void Paint::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    // 绘制基础图形
    // 可以设置Cap(一条线两端样式)、Join(两条线相交处的样式)、Line的样式
    p.setPen(Qt::red);
    p.drawLine(0, 0, 100, 150);
    p.drawRect(10, 10, 50, 50);
    p.setPen(QPen(Qt::green, 5));
    // 绘制普通的椭圆
    p.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
    p.setBrush(Qt::yellow);
    p.drawEllipse(70, 50, 50, 50);
    // 绘制椭圆-设置反走样，防锯齿（默认关闭的）
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
    p.setBrush(Qt::yellow);
    p.drawEllipse(140, 50, 50, 50);
    // 设置渐变
    p.setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient l(60, 50, 200, 200); // 设置渐变的起止位置
    l.setColorAt(0.2, Qt::white);
    l.setColorAt(0.6, Qt::green);
    l.setColorAt(1.0, Qt::black);
    // 渐变圆
    p.setBrush(QBrush(l));
    p.drawEllipse(220, 50, 50, 50);
    // 渐变线
    p.setPen(QPen(QBrush(l), 5));
    QTransform t;
    t.rotate(-30.0);
    p.setWorldTransform(t);
    p.drawLine(100, 100, 300, 300);
    // viewport and window TODO:
    t.rotate(0);
    p.setWorldTransform(t);
    p.setWindow(-50, -50, 50, 50);
    p.drawLine(-30, -20, 10, 20);
}
