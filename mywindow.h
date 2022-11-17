#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include <currencymodel.h>>

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
void initDirModel();

private slots:
void on_spinBox_valueChanged(int arg1);
void on_horizontalSlider_sliderMoved(int position);
void on_addButton_clicked();
void on_saveButton_clicked();
void on_clearCacheButton_clicked();
void on_loadCacheButton_clicked();
void on_mkdir();
void on_rmdir();

void on_searchInput_textChanged(const QString &arg1);

private:
Ui::MyWindow *ui;
QVector<QString> list;
QFileSystemModel *model;
QTreeView *tree;
QSortFilterProxyModel *modelProxy;
};

#endif // MYWINDOW_H
