#ifndef INVENTORY_H
#define INVENTORY_H
#include <QObject>
#include <QtWidgets>
#include <QSound> //аудио сопровождение
#include "inventoryitem.h"
class Inventory : public QTableWidget
{
    Q_OBJECT
public:
    Inventory(QWidget *parent = 0);
private slots:
    void clearCell(int row, int col);
private:
    const int rows = 3;
    const int cols = 3;
    int currentCount;
    QSound *obj;
    InventoryItem *startDrop_;
    InventoryItem *endDrop_;
signals:
    void cellDropped(int, int);
protected:
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

};

#endif // INVENTORY_H
