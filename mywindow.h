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
void addTable(const QString &s);
void addTree(const QString &s);

private slots:
void on_spinBox_valueChanged(int arg1);
void on_horizontalSlider_sliderMoved(int position);
void on_addButton_clicked();

void on_saveButton_clicked();

void on_clearCacheButton_clicked();

void on_loadCacheButton_clicked();

private:
Ui::MyWindow *ui;
QVector<QString> list;
};

#endif // MYWINDOW_H
