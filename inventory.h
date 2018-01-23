#ifndef INVENTORY_H
#define INVENTORY_H
#include <QObject>
#include <QtWidgets>
#include <QSound> //аудио сопровождение
#include "inventoryitem.h"
#include "db_manager.h"
class Inventory : public QTableWidget
{
    Q_OBJECT
public:
    Inventory(QWidget *parent = 0);
    ~Inventory();

private slots:
    void clearCell(int row, int col);
private:
    const int rows_ = 3;
    const int cols_ = 3;
    QSound *obj;
    InventoryItem *startDrop;
    InventoryItem *endDrop;
    DB_Manager* dbase;
signals:
    void cellDropped(int, int);
protected:
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

};

#endif // INVENTORY_H
