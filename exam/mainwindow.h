#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dsbridge.h"
#include "sorting.h"
#include "set.h"
#include <QMainWindow>
#include <QRandomGenerator>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QWidget>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_insbtn_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_randBtn_clicked();

    void on_removeBtn_clicked();

    void on_findBtn_clicked();

    void on_listBtn_clicked();

    void on_unionBtn_clicked();

    void on_intrsBnt_clicked();

    void on_sdiffBtn_clicked();

    void on_diffBtn_clicked();

    void on_comboSort_currentIndexChanged(int index);

    void on_comboType_currentIndexChanged(int index);

    void on_pushButton_9_clicked();

    void on_sortBtn_clicked();

private:


    Ui::MainWindow *ui;


    DSBridge<int,int>* ds = new DSBridge<int, int>();
    Set* s;
    Sorting<int,int> *sort;
    void createImage();
    void clear();
    void createSet(StlList<int, int>);
    void setTimePassed(QString);
    void wheelEvent(QWheelEvent *event);
};

#endif // MAINWINDOW_H
