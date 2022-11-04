#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "mywindow.h"
#include "mdialog.h"
#include "paint.h"

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
virtual void timerEvent(QTimerEvent*) override;
void init();

/*
 * Q_SIGNALS/Q_SLOTS/Q_EMIT代替signals、slots、emit
 * 在第三方库这些关键字可能已经被使用了
 *
 * Q_SIGNAL和Q_SIGNAL区别：（Q_SLOT和Q_SLOTS区别）
 *     这两个都是对signals的代替；
 *     Q_SIGNAL是定义单个信号，不需要衔接冒号
 *     Q_SIGNALS定义多个信号，需要衔接冒号
 */
Q_SIGNAL // Q_SIGNAL // Q_SIGNALS: // signals:
void my_signal();

Q_SIGNAL
void my_signal2(const QString &qs);

/*
 * 定义槽函数
    public slots: 表示任何信号signal都可以和这个槽连接
    private slots: 表示只有自己的信号可以和这个槽连接
    protected slots: 表示只有自己和子类可和这个槽连接
 */

private Q_SLOTS: // private Q_SLOT // private slots:
// 自定义connect
void custom_click_listener(int a);
void custom_click_listener2();
void custom_trigger_fn();
void custom_trigger_fn(const QString &qs);
void custom_trigger_action();
// QT自动connect
void on_button_exit_clicked();
void on_button_jump_clicked();
void on_DateButton_clicked();
void on_DateButton_2_clicked();
void on_MDialogButton_clicked();
void on_PaintButton_clicked();

private:
int timerID1 = NULL;
QTimer *timerID2 = nullptr;
bool isDateFlag = true;
bool isDateFlag_2 = true;
Ui::MainWindow *ui = nullptr;
QSignalMapper *sp = nullptr;
MyWindow *child_window = nullptr;
MDialog *mdialog = nullptr;

};
#endif // MAINWINDOW_H
