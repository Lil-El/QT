#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QWidget>

// 在ui文件中修改顶级Widget的name
QT_BEGIN_NAMESPACE
namespace Ui {
class MyWindow;
}
QT_END_NAMESPACE

class MyWindow : public QWidget
{
Q_OBJECT

public:
MyWindow(QWidget *parent = nullptr);
~MyWindow();

private slots:
void on_spinBox_valueChanged(int arg1);
void on_horizontalSlider_sliderMoved(int position);

private:
Ui::MyWindow *ui;
};

#endif // MYWINDOW_H
