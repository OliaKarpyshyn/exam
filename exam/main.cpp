#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <tuple>
#include "dclist.h"
#include "bplustree.h"
#include "rbtree.h"
#include "stllist.h"
#include "stlmap.h"
#include "stlvector.h"
#include "code.h"
#include "sorting.h"
#include "datastructure.h"

int main(int argc, char *argv[])
{
    Sorting<int,int> s;
   /* DSBridge<int, int> k;
    k.insert(1,5);
    k.insert(3,4);
    k.insert(2,8);
    k.insert(7,1);
    k.insert(5,2);
   // k.remove(5);
   // vector<tuple<int,int>> v =k.getKeys();
   // s.sort(v,2);
    //k.graphviz("picture.dat");
    for (auto const& i : v) {
        qDebug()<<get<0>(i);
    }
*/
    QFile styleSheet("..\\exam\\stylesheet.qss"); //path where the file is stored
    QApplication a(argc, argv);
    if (styleSheet.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(styleSheet.readAll());
    }
    MainWindow w;
    w.show();


    return a.exec();
}
