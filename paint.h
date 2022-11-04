#ifndef PAINT_H
#define PAINT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Paint;
}
QT_END_NAMESPACE

class Paint : public QWidget
{
Q_OBJECT

public:
explicit Paint(QWidget *parent = nullptr);
~Paint();

protected:
void paintEvent(QPaintEvent *event);

private:
Ui::Paint *ui;
};

#endif // PAINT_H
