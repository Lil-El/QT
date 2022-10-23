#ifndef MDIALOG_H
#define MDIALOG_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class mdialog;
}

class MDialog : public QDialog
{
Q_OBJECT

public:
MDialog(QWidget *parent = nullptr);
~MDialog();

signals:
void mdOK(const QString&qs);

private slots:
void onmdOK(const QString&qs);
void on_buttonBox_accepted();

private:
Ui::mdialog *ui = nullptr;

};

#endif // MDIALOG_H
