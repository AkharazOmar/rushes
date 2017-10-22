#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationDirPath());

    QFile f("rr_theme.qss");
    //QFile f("QTDark.stylesheet");
    //QFile f("RRDark.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

    MainWindow w;

    w.setWindowTitle("CatalogR v" + a.applicationVersion());

    w.show();

    return a.exec();    
}
