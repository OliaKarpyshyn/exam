#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include "dclist.h"
#include "bplustree.h"
#include "datastructure.h"

int main(int argc, char *argv[])
{

    BplusTree<int, int> k;
    k.insert(1,2);
    k.insert(2,2);
    k.insert(3,3);
    k.insert(4,2);
    k.insert(5,2);
    k.remove(2);
    k.graphviz("picture.dat");


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
