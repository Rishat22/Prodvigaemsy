#include "inventory.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    this->setRowCount(rows);
    this->setColumnCount(cols);

    for(int i = 0; i < rows; i++)
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
    obj = new QSound(":/resources/cutapple.wav");
    //this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDefaultDropAction(Qt::DropAction::MoveAction);
    //this->setAcceptDrops(true);
    //this->setDropIndicatorShown(true);
    startDrop_ = new InventoryItem();
    endDrop_ = new InventoryItem();

    for(int row = 0; row < this->rowCount(); row++)
    {
        for(int col = 0; col < this->columnCount(); col++)
        {
            this->setItem(row, col, new InventoryItem());
        }
    }
    //Data_base:
    dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite

}

Inventory::~Inventory()
{

}


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
            startDrop_ = invItemTarget;
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
        invItemTarget->decreaseCout();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        if(invItemTarget->getCount() == 0)
        {
            obj->play();
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
    //dbase->insertIntoEquipment((row*3)+(col),"Apple",0);
    //emit ;
}

void Inventory::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << event->mimeData()->text();
    if(event->mimeData()->hasText())
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void Inventory::dragMoveEvent(QDragMoveEvent * event)
{

}


void Inventory::dropEvent(QDropEvent *event)
{
    QTableWidgetItem *targetItem = itemAt(event->pos());

    InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
    endDrop_ = invItemTarget;
    if(startDrop_ != endDrop_)
    {
        invItemTarget->increaseCount(event->mimeData()->text().toInt());

        invItemTarget->setIcon_();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        event->acceptProposedAction();
//        qDebug()<<"startDrop_ "<<startDrop_->row()<<(startDrop_->column());
        qDebug()<<"startDrop_ "<<(startDrop_->row()*3) + (startDrop_->column()+1);

        dbase->updateEquipment((startDrop_->row()*3) + (startDrop_->column()+1), 0);

        emit cellDropped(startDrop_->row(),startDrop_->column());
        qDebug()<<"endDrop_ "<<(endDrop_->row()*3) + (endDrop_->column()+1);

        dbase->updateEquipment((endDrop_->row()*3) + (endDrop_->column()+1), endDrop_->getCount());


    }
    else
        event->ignore();
}


