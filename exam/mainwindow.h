#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dsbridge.h"
#include "set.h"
#include <QMainWindow>

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

private:


    Ui::MainWindow *ui;


    DSBridge<int,int>* ds = new DSBridge<int, int>();
    Set* s;
    void createImage();
    void clear();
    void createSet(StlList<int, int>);
};

#endif // MAINWINDOW_H
