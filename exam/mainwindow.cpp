#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s= new Set;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createImage(){

    string pathToFile ="";
    string pathToImage= pathToFile;
    pathToFile+="picture.dot";
    pathToImage+="picture.png";
    ds->ds[ds->currentStructure]->graphviz(pathToFile.c_str());
    string cmdCommand = "..\\exam\\graphviz\\bin\\dot.exe -Tpng " + pathToFile + " -o " + pathToImage;

    system(cmdCommand.c_str());
    QImage image(pathToImage.c_str());


    QGraphicsPixmapItem *item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    QGraphicsScene* scene;

    QGraphicsView *view = (ds->currentStructure==0)? ui->graphicsView : ui->graphicsView_2;

    if(view->scene()==nullptr)
    {
        scene = new QGraphicsScene;
    }
    else
    {
        scene = view->scene();
        scene->removeItem(scene->items().at(0));
    }
    view->setScene(scene);
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
    scene->addItem( item );
    item->setPos( 0, 0 );
}

void MainWindow::clear()
{
    QGraphicsView *view = (ds->currentStructure==0)? ui->graphicsView : ui->graphicsView_2;

    if(view->scene()!=nullptr)
    {
        view->scene()->clear();
        view->scene()->deleteLater();
    }
}

void MainWindow::createSet(StlList<int, int> map)
{
    s->setModal(true);
    s->show();

    string pathToFile ="";
    string pathToImage= pathToFile;
    pathToFile+="picture.dot";
    pathToImage+="picture.png";
    map.graphviz(pathToFile.c_str());
    string cmdCommand = "..\\exam\\graphviz\\bin\\dot.exe -Tpng " + pathToFile + " -o " + pathToImage;

    system(cmdCommand.c_str());
    QImage image(pathToImage.c_str());


    QGraphicsPixmapItem *item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    QGraphicsScene* scene;

    QGraphicsView *view = s->getView();

    if(view->scene()==nullptr)
    {
        scene = new QGraphicsScene;
    }
    else
    {
        scene = view->scene();
        scene->removeItem(scene->items().at(0));
    }
    view->setScene(scene);
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
    scene->addItem( item );
    item->setPos( 0, 0 );

}

void MainWindow::on_insbtn_clicked()
{
    int k = QInputDialog::getInt(this, "Insert", "Enter key");
    int v = QInputDialog::getInt(this, "Insert", "Enter value");
    ds->insert(k, v);
    createImage();

}

void MainWindow::on_radioButton_clicked()
{
    ds->currentStructure = 0;
}

void MainWindow::on_radioButton_2_clicked()
{
    ds->currentStructure = 1;
}

void MainWindow::on_randBtn_clicked()
{
    int k = QInputDialog::getInt(this, "Random insert", "Enter amount");
    for(int i = 0; i<k; i++)
        ds->insert(QRandomGenerator::global()->bounded(0,20), QRandomGenerator::global()->bounded(0,200));

    createImage();
}

void MainWindow::on_removeBtn_clicked()
{
    int k = QInputDialog::getInt(this, "Remove", "Enter key");
    ds->remove(k);
    createImage();

}

void MainWindow::on_findBtn_clicked()
{
    int k = QInputDialog::getInt(this, "Find", "Enter key");
    auto value = ds->find(k);

    QString message = "Key: " + QString::number(k) + "\nValue: " + QString::number(value);
    QMessageBox::information(this,"Result",message);
}

void MainWindow::on_listBtn_clicked()
{
    QMessageBox::information(this,"Keys",ds->getKeys());

}

void MainWindow::on_unionBtn_clicked()
{
    s->setLabel("Union");
    vector<tuple<int,int>> v1 = ds->ds[0]->getKeys(), v2 = ds->ds[1]->getKeys();
    StlList<int,int> m;
    for(auto val : v1)
        m.insert(get<0>(val), get<1>(val));

    for(auto val : v2)
        m.insert(get<0>(val), get<1>(val));

    createSet(m);
}
