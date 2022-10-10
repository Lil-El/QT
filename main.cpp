#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "hello_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    /*
     * 不使用自定义的MainWindow对象，直接使用QMainWindow
     * 这种方式不推荐，不利于二次封装
        QApplication a(argc, argv);//定义一个Qt应用程序对象

        QMainWindow *w = new QMainWindow();  //新建一个主窗口对象
        Ui::Mainwindow createUi;  //createUi并不是一个真正的窗口对象，相当于我们上面的那个私有成员Ui::MainWindow *ui
        createUi.setupUi(w);  //createUi是创建GUI的工具，将w这个主窗口作为参数传进去

        w->show();  //展示窗口
        return a.exec();
    */
    MainWindow w;
    w.show();
    return a.exec();
}
