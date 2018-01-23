#ifndef APPLES_H
#define APPLES_H

#include <QObject>
#include <QtWidgets>
#include "inventoryitem.h"
#include "db_manager.h"
class Apples: public QTableWidget
{
    Q_OBJECT
public:
    Apples(QWidget *parent = 0);

private:
    const QString iconPath_ = ":/resources/appleIcon.png";
    const QString itemType_ = "Apple";
    InventoryItem *startDrop;
    InventoryItem *endDrop;
    DB_Manager* dbase;
protected:
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

signals:
    void externalItem();
};

#endif // APPLES_H
