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
    // 校准
    t.rotate(+30); // 上面减了30，这里加30，恢复初始状态
    p.setWorldTransform(t);
    p.setPen(QPen(Qt::yellow, 3));
    p.drawLine(0, 0, 200, 200);
    /* viewport and window: TODO: 博客-https://www.cnblogs.com/realid/archive/2013/05/05/3061312.html
     * 物理窗口的size：500,200
     * setWindow(0, 0, 200, 200)：逻辑坐标，窗口的右下角（物理500,200的位置）的逻辑坐标为200,200；即使窗口被放大、缩小右下角都是200,200
     * setViewport(0, 0, 200, 200)：指定窗体可绘制的范围，物理坐标200,200的位置的坐标为500,200；一条线的端点为500,200，实际是在200,200的物理位置上
     * 联合使用，窗口的物理范围0,0,200,200的逻辑坐标为window的坐标
     *         p.setWindow(0, 0, 200, 200);
               p.setViewport(100, 100, 200, 200);
               p.drawLine(0, 0, 200, 200);
       划定范围100,100,200,200的物理范围；设置左上、右下的逻辑坐标为0,0和200,200
       绘制一条0,0,200,200的线，相当于将物理范围100,100,200,200的对角线连接了起来
     */
    p.setPen(QPen(Qt::blue, 3));
    p.setWindow(0, 0, 200, 200);
    p.setViewport(100, 100, 200, 200); // viewport默认和窗口是一样大的
    p.drawLine(0, 0, 200, 200);
}
