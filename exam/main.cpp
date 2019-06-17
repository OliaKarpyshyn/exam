#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QFile styleSheet("C:\\Users\\Alexandra\\Documents\\QT\\GOL\\stylesheet.qss"); //path where the file is stored
    QApplication a(argc, argv);
    if (styleSheet.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(styleSheet.readAll());
    }
    MainWindow w;
    w.show();

    return a.exec();
}
