#include "inventory.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    this->setRowCount(rows_);
    this->setColumnCount(cols_);
    for(int i = 0; i < rows_; i++)
    {

        this->setRowHeight(i, 154);
        this->setColumnWidth(i, 154);
    }

    this->horizontalScrollBar()->hide();
    this->verticalScrollBar()->hide();
    // inventoryItem = new InventoryItem();
    connect(this, SIGNAL(cellDropped(int,int)), this, SLOT(clearCell(int,int)));

    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    sound = new QSound(":/resources/cutapple.wav");
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDefaultDropAction(Qt::DropAction::MoveAction);
    startDrop = new InventoryItem();
    endDrop = new InventoryItem();

    for(int row = 0; row < this->rowCount(); row++)
    {
        for(int col = 0; col < this->columnCount(); col++)
        {
            this->setItem(row, col, new InventoryItem());
        }
    }
    externalItem = false;
    //Data_base:
    dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite


}

Inventory::~Inventory(){}


void Inventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QTableWidgetItem *targetItem = itemAt(event->pos());

        InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
        if(!targetItem || invItemTarget->getCount() == 0)
            return;
        else
        {
            startDrop = invItemTarget;
            QByteArray itemData;
            QDataStream dataStream(&itemData, QIODevice::WriteOnly);
            dataStream << 100;

            QMimeData *mimeData = new QMimeData;
            mimeData->setText(QString::number(invItemTarget->getCount()));

            QDrag *drag = new QDrag(this);
            drag->setMimeData(mimeData);

            Qt::DropAction dropAction = drag->start(Qt::MoveAction);
        }

    }
    if (event->button() == Qt::RightButton)
    {

        QTableWidgetItem *targetItem = itemAt(event->pos());
        InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
        int beforeDecreaseCount = invItemTarget->getCount();
        invItemTarget->decreaseCout();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        if(invItemTarget->getCount() == 0)
        {
            if(beforeDecreaseCount != 0)
                sound->play();
            dbase->updateEquipment((invItemTarget->row()*3) + (invItemTarget->column()+1), 0);
            clearCell(invItemTarget->row(),invItemTarget->column());
        }
        dbase->updateEquipment((invItemTarget->row()*3) + (invItemTarget->column()+1), invItemTarget->getCount());
    }
}
void Inventory::clearCell(int row, int col)
{
    InventoryItem* item = new InventoryItem(); //Вот здесь непонятно!
    this->setItem(row,col, item);
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasText())
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void Inventory::dragMoveEvent(QDragMoveEvent * event){}

void Inventory::dropEvent(QDropEvent *event)
{

    QTableWidgetItem *targetItem = itemAt(event->pos());

    InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
    endDrop = invItemTarget;

    if(startDrop != endDrop && externalItem == false)
    {
        invItemTarget->increaseCount(event->mimeData()->text().toInt());

        invItemTarget->setIcon_();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        event->acceptProposedAction();
        dbase->updateEquipment((startDrop->row() * 3) + (startDrop->column() + 1), 0);
        emit cellDropped(startDrop->row(),startDrop->column());
        dbase->updateEquipment((endDrop->row()*3) + (endDrop->column()+1), endDrop->getCount());
        externalItem = false;
    }

    else if(startDrop != endDrop && externalItem == true)
    {
        invItemTarget->increaseCount(event->mimeData()->text().toInt());
        invItemTarget->setIcon_();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        event->acceptProposedAction();
        dbase->updateEquipment((endDrop->row()*3) + (endDrop->column()+1), endDrop->getCount());
        externalItem = false;
    }

    else
        event->ignore();
}


void Inventory::changeExternalItemValue()
{
    externalItem = true;
}
