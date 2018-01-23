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

    QString getItemPath() const;
    QString getItemType() const;

private:
    QString itemPath_;
    QString itemType_;
    int count_;

};

#endif // INVENTORYITEM_H
