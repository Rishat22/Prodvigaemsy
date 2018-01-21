#include "inventoryitem.h"

InventoryItem::InventoryItem()
{
    count_ = 0;
}

void InventoryItem::setIcon_()
{
    this->setData(Qt::DecorationRole, QVariant(QPixmap(":/resources/appleIcon.png").scaled(110,110)));
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
