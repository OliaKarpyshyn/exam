#include "set.h"
#include "ui_set.h"

Set::Set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
}

Set::~Set()
{
    delete ui;
}

QGraphicsView* Set::getView(){
    return ui->graphicsView;
}

void Set::setLabel(QString s)
{
    ui->label->setText(s);
}
