#include "mdialog.h"
#include "ui_mdialog.h"
#include <iostream>
#include <QApplication>
using namespace std;

class MinoEvent : public QEvent {
public:
    MinoEvent(int a) : QEvent(QEvent::Type(QEvent::registerEventType(QEvent::User + 997))),  age(a) { };
    ~MinoEvent() {};
    int getAge() {
        return age;
    }
private:
    int age;
};

MDialog::MDialog(QWidget *parent) : QDialog(parent), ui(new Ui::mdialog)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
    /*
     * connect中只有类型，没有参数
     * SIGNAL和SLOT的参数类型、数量必须一样
     * 如果不一样，那么以SLOT为准，SIGNAL中多的就会被忽略。SIGNAL(x(int, string, bool)), SLOT(x(int)); string/bool忽略
     */
    connect(this, SIGNAL(mdOK(const QString&)), this, SLOT(onmdOK(const QString&)));
    registeMyEvent();
}

/*
 * 事件处理实际上是五个层次：重定义事件处理函数，重定义event()函数，为单个组件安装事件过滤器，为 QApplication 安装事件过滤器，重定义 QCoreApplication 的 notify()函数。这几个层次的控制权是逐层增大的。
 * 例如，textField.installEventFilter(obj)，则如果有事件发送到textField 组件是，会先调用 obj->eventFilter()函数，然后才会调用 textField.event()。
 * 事件过滤器和被安装的组件必须在同一线程，否则，过滤器不起作用
*/

void MDialog::mousePressEvent(QMouseEvent *ev) {
    cout << ev->position().x() << endl;
}

void MDialog::closeEvent(QCloseEvent *ev) {
    // accept()接收事件，不会向父级传递了；ignore()拒绝事件，让父级处理；也可以直接调用parent的事件函数QWidget::mousePressEvent(ev);
    if(true) {
        ev->accept();
    } else {
        ev->ignore();
    }
}

/*
 * event()是分发不同的事件给事件处理器，理所当然在其他处理器(mousePressEvent等)之前执行
*/
bool MDialog::event(QEvent *ev) {
    if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(ev);
        return true; // 返回true表示事件已处理完毕（不会执行上面的mousePressEvent函数），反之会继续寻找这个事件的下一个处理器
    }
    // 自定义事件处理1
    if (ev->type() == 1997) {
        qDebug() << "event() receive custom event 1997";
    }
    // 先MDialog::event()处理，然后交由上级处理；
    return QDialog::event(ev); // 其他的都正常传递执行
}

/*
 * 事件过滤器：判断组件是否接收、过滤事件
 * 例如要为dialog弹窗中很多组件做事件处理，要给所有组件event()。为了方便写一个eventFilter，为组件进行install
*/
bool MDialog::eventFilter(QObject *obj, QEvent *ev) {
    if(obj == ui->lineEdit) {
        if (ev->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(ev);
            return true;
        } else {
            return false;
        }
    } else {
        // 交给父级处理
        return QDialog::eventFilter(obj, ev);
    }
}

// 自定义事件
void MDialog::registeMyEvent() {
    MinoEvent event(25);
    QApplication::sendEvent(this, &event); // sendEvent和postEvent
}
// 自定义事件处理器2
void MDialog::customEvent(QEvent *ev) {
    qDebug() << "receive custom evnet, eventType is: " << ev->type();
    MinoEvent *me = dynamic_cast<MinoEvent*>(ev);
    qDebug() << "receive custom evnet, event data is: " << me->getAge();
}

MDialog::~MDialog() {
    delete ui;
}

void MDialog::onmdOK(const QString &qs) {
    cout << "onmdOK" << endl;
}

void MDialog::on_buttonBox_accepted()
{
    QString qs = ui->lineEdit->text();
    emit mdOK(qs); // 一对多，1.发送给onmdOK，2.发送给mainwindow的custom_trigger_fn()
}

