#ifndef APPLES_H
#define APPLES_H

#include <QObject>
#include <QtWidgets>
#include "inventoryitem.h"

class Apples: public QTableWidget
{
    Q_OBJECT
public:
    Apples(QWidget *parent = 0);
private:
    InventoryItem *startDrop_;
    InventoryItem *endDrop_;
protected:
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
};

#endif // APPLES_H
