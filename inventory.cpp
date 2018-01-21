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

    connect(this, SIGNAL(cellDropped(int,int)), this, SLOT(clearCell(int,int)));
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    obj = new QSound("cutApple.wav");
    //this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDefaultDropAction(Qt::DropAction::MoveAction);
    //this->setAcceptDrops(true);
    //this->setDropIndicatorShown(true);
    startDrop_ = new InventoryItem();
    endDrop_ = new InventoryItem();
    currentCount = 0;
}


void Inventory::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QTableWidgetItem *targetItem = itemAt(event->pos());

        InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
        startDrop_ = invItemTarget;
        if(!invItemTarget)
            return;

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << 100;

        QMimeData *mimeData = new QMimeData;
        mimeData->setText(QString::number(invItemTarget->getCount()));

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);

        Qt::DropAction dropAction = drag->start(Qt::MoveAction);

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
            clearCell(invItemTarget->row(),invItemTarget->column());
        }
    }
}
void Inventory::clearCell(int row, int col)
{
    InventoryItem* item = new InventoryItem(); //Вот здесь непонятно!
    this->setItem(row,col, item);

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
        emit cellDropped(startDrop_->row(),startDrop_->column());
    }
    else
        event->ignore();
}


