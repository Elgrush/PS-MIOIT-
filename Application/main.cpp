#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    //const QStringList uiLanguages = QStringList("de");
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Application_" + QLocale(locale).name();
        if (translator.load(qApp->applicationDirPath()+"/../../" + baseName)) {
            a.installTranslator(&translator);
            break;
        }

    }

    MainWindow w;
    w.show();
    return a.exec();
}
