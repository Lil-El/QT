#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// 单一继承：继承QMainWindow，将Ui::MainWindow作为成员变量
// TODO: 也可以使用多重继承：继承QmainWindow, Ui::MainWindow
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
MainWindow(QWidget *parent = nullptr);
~MainWindow();

// QT槽函数
private slots:
// 自定义connect
void custom_click_listener(int a);
void custom_click_listener2();
// QT自动connect
void on_button_exit_clicked();

private:
Ui::MainWindow *ui;
QSignalMapper *sp;

};
#endif // MAINWINDOW_H
