#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>
#include <chrono>
#include <vector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = new Set;
    sort = new Sorting<int,int>;
    ui->statusBar->showMessage(" ");

    ui->comboSort->addItem("Quick sort");
    ui->comboSort->addItem("Heap sort");
    ui->comboSort->addItem("Selection sort");

    ui->comboType->addItem("STL List");
    ui->comboType->addItem("STL Map");
    ui->comboType->addItem("STL Vector");
    ui->comboType->addItem("Doublelinked cyclic List");
    ui->comboType->addItem("Red-black tree");
    ui->comboType->addItem("B+ tree");

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

void MainWindow::setTimePassed(QString s)
{
    ui->statusBar->showMessage("Time:" + s + " microseconds");
}

void MainWindow::on_insbtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    auto begn = std::chrono::steady_clock::now();

    int k = QInputDialog::getInt(this, "Insert", "Enter key");
    int v = QInputDialog::getInt(this, "Insert", "Enter value");
    ds->insert(k, v);
    createImage();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begn);
    setTimePassed(QString::number(elapsed_ms.count()));

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
    auto begin = std::chrono::steady_clock::now();

    int k = QInputDialog::getInt(this, "Random insert", "Enter amount");
    for(int i = 0; i<k; i++)
        ds->insert(QRandomGenerator::global()->bounded(0,20), QRandomGenerator::global()->bounded(0,200));

    createImage();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

void MainWindow::on_removeBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    int k = QInputDialog::getInt(this, "Remove", "Enter key");
    ds->remove(k);
    createImage();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));

}

void MainWindow::on_findBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    int k = QInputDialog::getInt(this, "Find", "Enter key");
    auto value = ds->find(k);

    QString message = "Key: " + QString::number(k) + "\nValue: " + QString::number(value);
    QMessageBox::information(this,"Result",message);


    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

void MainWindow::on_listBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    QMessageBox::information(this,"Keys",ds->getKeys());

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

void MainWindow::on_unionBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    s->setLabel("Union");
    vector<tuple<int,int>> v1 = ds->ds[0]->getKeys(), v2 = ds->ds[1]->getKeys();
    StlList<int,int> m;
    for(auto val : v1)
        m.insert(get<0>(val), get<1>(val));

    for(auto val : v2)
        m.insert(get<0>(val), get<1>(val));

    createSet(m);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

void MainWindow::on_intrsBnt_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    s->setLabel("Intersection");
    StlList<int,int> l;
    vector<tuple<int,int>> v1 = ds->ds[0]->getKeys(), v2 = ds->ds[1]->getKeys(), inters;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                              v2.begin(),v2.end(),
                              back_inserter(inters));
    for(auto val : inters)
        l.insert(get<0>(val), get<1>(val));

    createSet(l);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}


void MainWindow::on_sdiffBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    s->setLabel("SymDifference");
    vector<tuple<int,int>> v1 = ds->ds[0]->getKeys(), v2 = ds->ds[1]->getKeys(),un, inters;
    StlList<int,int> m;
    for(auto val : v1)
        un.push_back(val);//m.insert(get<0>(val), get<1>(val));

    for(auto val : v2)
        un.push_back(val);//m.insert(get<0>(val), get<1>(val));

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                              v2.begin(),v2.end(),
                              back_inserter(inters));
    bool f=false;
    for(auto val : un){
        for(auto v : inters){
        if(get<0>(val)==get<0>(v) || get<1>(val)==get<1>(v)) {f=true; break;}
    }
        if(!f) m.insert(get<0>(val), get<1>(val));
        f=false;
}

    createSet(m);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));

}

void MainWindow::on_diffBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    s->setLabel("Difference");
    vector<tuple<int,int>> v1 = ds->ds[0]->getKeys(), v2 = ds->ds[1]->getKeys(), inters;
    StlList<int,int> m;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_intersection(v1.begin(),v1.end(),
                              v2.begin(),v2.end(),
                              back_inserter(inters));
    bool f=false;
    for(auto val : v1){
        for(auto v : inters){
        if(get<0>(val)==get<0>(v) || get<1>(val)==get<1>(v)) {f=true; break;}
    }
        if(!f) m.insert(get<0>(val), get<1>(val));
        f=false;
}

    createSet(m);

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

void MainWindow::on_comboSort_currentIndexChanged(int index)
{
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));

}

void MainWindow::on_comboType_currentIndexChanged(int index)
{
    auto begin = std::chrono::steady_clock::now();

    ds->currentStructure? ui->label_2->setText(ui->comboType->currentText()):ui->label->setText(ui->comboType->currentText());

    ds->changeType(index);
    clear();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));


}

void MainWindow::on_pushButton_9_clicked()
{

}

void MainWindow::on_sortBtn_clicked()
{
    auto begin = std::chrono::steady_clock::now();

    if(ui->comboType->currentIndex()!=4&&ui->comboType->currentIndex()!=5){

    int choice = ui->comboSort->currentIndex();
    vector<tuple<int,int>> before = ds->ds[ds->currentStructure]->getKeys();
    sort->sort(before, choice);

    for(auto val : before){
        ds->ds[ds->currentStructure]->remove(get<0>(val));
    }

    for(auto val : before){
        ds->ds[ds->currentStructure]->insert(get<0>(val), get<1>(val));
    }

    createImage();
}
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));

}
