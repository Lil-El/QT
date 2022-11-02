#ifndef MDIALOG_H
#define MDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class mdialog;
}

class MDialog : public QDialog
{
Q_OBJECT

public:
MDialog(QWidget *parent = nullptr);
~MDialog();

// TODO: 事件接收与忽略
// override覆盖QWidget中virtual定义的事件函数
protected:
void mousePressEvent(QMouseEvent *ev) override;

signals:
void mdOK(const QString&qs);

private slots:
void onmdOK(const QString&qs);
void on_buttonBox_accepted();

private:
Ui::mdialog *ui = nullptr;

};

#endif // MDIALOG_H
