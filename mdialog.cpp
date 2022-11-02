#include "mdialog.h"
#include "ui_mdialog.h"
#include <iostream>
using namespace std;

MDialog::MDialog(QWidget *parent) : QDialog(parent), ui(new Ui::mdialog)
{
    ui->setupUi(this);
    /*
     * connect中只有类型，没有参数
     * SIGNAL和SLOT的参数类型、数量必须一样
     * 如果不一样，那么以SLOT为准，SIGNAL中多的就会被忽略。SIGNAL(x(int, string, bool)), SLOT(x(int)); string/bool忽略
     */
    connect(this, SIGNAL(mdOK(const QString&)), this, SLOT(onmdOK(const QString&)));
}

void MDialog::mousePressEvent(QMouseEvent *ev) {
    cout << ev->x() << endl;
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

