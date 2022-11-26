#ifndef DND_H
#define DND_H
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dnd;
}
QT_END_NAMESPACE

class dnd : public QWidget
{
    Q_OBJECT

public:
    explicit dnd(QWidget *parent = nullptr);
    ~dnd();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::Dnd *ui;
    bool readFile(const QString &fileName);
};

#endif // DND_H
