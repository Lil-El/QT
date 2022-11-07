#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * i18n:
     * hello_zh_CN.ts仅仅是我们自己代码中写的文字；
     * 如果要修改内置的弹窗等widget的文字，需要在Qt的安装目录中找到相关文件，然后进行国际化设置并加载，
     * 【qm】 - D:\Program_Files\Qt\6.4.0\mingw_64\translations
     * 【ts】 - D:\Program_Files\Qt\6.4.0\Src\qttranslations\translations
     * ts 通过lrelease发布 生成 qm
     */
    // 自己代码中的tr()
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) { // locale == zh_CN
        const QString baseName = "hello_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // 内置widget，dialog，右键菜单等国际化
    QTranslator translator2;
    if (translator2.load("D:/Program_Files/Qt/6.4.0/mingw_64/translations/qt_zh_CN.qm")) {
        a.installTranslator(&translator2);
    } else {
        qDebug() << "load translator file faile.";
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

    /**
     * Qt 也是支持 HTML 解析的。
     * QLabel label("<h1><font color='red'>Hello</font> <span style='color: green;'>World</span>!</h1>");
     * label.show();
     *
     * 也可以直接展示Label，不用MainWindow对象
     * QLabel *label = new QLabel("Hello"); label->show();
     */
    // 一个程序中只能有一个QMainWindow实例
    MainWindow w;
    w.show();
    return a.exec();
}

















