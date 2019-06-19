#ifndef SET_H
#define SET_H

#include <QDialog>
#include <QGraphicsView>
#include <QLabel>

namespace Ui {
class Set;
}

class Set : public QDialog
{
    Q_OBJECT

public:
    explicit Set(QWidget *parent = nullptr);
    ~Set();
    QGraphicsView* getView();
    void setLabel(QString);

private:
    Ui::Set *ui;
};

#endif // SET_H
