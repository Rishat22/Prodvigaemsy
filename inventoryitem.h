#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <QObject>
#include <QtWidgets>
#include <QTableWidgetItem>
class InventoryItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:

    InventoryItem();
    void setIcon_();
    void increaseCount(int count);
    void setCount(int count);
    int getCount();
    void decreaseCout();

private:
    const QString iconPath_ = ":/resources/icon.png";
    int count_;
};

#endif // INVENTORYITEM_H
