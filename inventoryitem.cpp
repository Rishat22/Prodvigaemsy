#include "inventoryitem.h"

InventoryItem::InventoryItem()
{
    itemPath_ = ":/resources/appleIcon.png";
    itemType_ = "Apple";
    //dbase = new DB_Manager();
    count_ = 0;
}

void InventoryItem::setIcon_()
{
    this->setData(Qt::DecorationRole, QVariant(QPixmap(itemPath_).scaled(110,110)));
}


void InventoryItem::increaseCount(int count)
{
    count_ = count_  + count;
}

void InventoryItem::setCount(int count)
{
    count_ = count;
}

int InventoryItem::getCount()
{
    return count_;
}

void InventoryItem::decreaseCout()
{
    if(count_ > 0)
        setCount(count_ - 1);
}

QString InventoryItem::getItemPath() const
{
    return itemPath_;
}

QString InventoryItem::getItemType() const
{
    return itemType_;
}
