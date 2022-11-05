#include "paint.h"
#include "ui_paint.h"
#include <iostream>
#include <QPainter>
#include <QPen>
#include <QLinearGradient>
#include <QDir>
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
    // 图片: Qt默认只支持png图片。jpg的需要添加其他库
    p.setWindow(0, 0, 500, 200);
    p.setViewport(0, 0, 500, 200);
    // 设置相对路径
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    // QDir dir; qDebug() << dir.currentPath();
    QPixmap pixmap;
    pixmap.load("img.png"); // 绝对路径：D://Work/QT/Hello/img.png；相对路径需要设置上面的代码
    p.drawPixmap(10, 140, 50, 50, pixmap); // x y w h

    /*
     * Graphics View 提供了一个 QGraphicsScene 作为场景，即是我们添加图形的空间，相当于整个世界；
     * 一个 QGraphicsView 作为视口，也就是我们观察的窗口，相当于照相机的取景框，这个取景框可以覆盖整个场景，也可以是场景的一部分；
     * 一些 QGraphicsItem 作为图形元件，以便 scene 添加，Qt 内置了很多图形，比如 line、polygon 等，都是继承自 QGraphicsItem。
     */
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->addLine(10, 10, 100, 100);
    ui->graphicsView->setWindowTitle("Graphics View");
}
