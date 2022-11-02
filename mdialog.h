#ifndef MDIALOG_H
#define MDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QCloseEvent>

namespace Ui {
class mdialog;
}

class MDialog : public QDialog
{
Q_OBJECT

public:
MDialog(QWidget *parent = nullptr);
~MDialog();
void registeMyEvent();

// override覆盖QWidget中virtual定义的事件函数
protected:
void mousePressEvent(QMouseEvent *ev) override;
void closeEvent(QCloseEvent *ev) override;
bool event(QEvent *ev) override;
bool eventFilter(QObject *obj, QEvent *ev) override;
void customEvent(QEvent *ev) override;

signals:
void mdOK(const QString&qs);

private slots:
void onmdOK(const QString&qs);
void on_buttonBox_accepted();

private:
Ui::mdialog *ui = nullptr;

};

#endif // MDIALOG_H
