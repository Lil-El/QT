#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "mywindow.h"

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
virtual void timerEvent(QTimerEvent*);

Q_SIGNAL
void my_signal();

// QT槽函数
private slots: // Q_SLOT
// 自定义connect
void custom_click_listener(int a);
void custom_click_listener2();
void custom_trigger_fn();
// QT自动connect
void on_button_exit_clicked();
void on_button_jump_clicked();

private:
int timerID1 = NULL;
Ui::MainWindow *ui = nullptr;
QSignalMapper *sp = nullptr;
MyWindow *child_window = nullptr;

};
#endif // MAINWINDOW_H
