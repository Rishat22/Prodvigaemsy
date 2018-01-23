#include "apples.h"

Apples::Apples(QWidget *parent) :
    QTableWidget(parent)
{
    this->setRowCount(1);
    this->setColumnCount(1);

    this->setRowHeight(0, 154);
    this->setColumnWidth(0, 154);

    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    this->setDragEnabled(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragDropMode(QAbstractItemView::DragOnly);
    this->setDropIndicatorShown(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    startDrop = new InventoryItem();
    endDrop = new InventoryItem();
    //data base
    dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite
    dbase->insertIntoItems(startDrop->getItemType(),startDrop->getItemPath()); //добавление элемента в таблицу Items

}


void Apples::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QTableWidgetItem *targetItem = itemAt(event->pos());

        InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
        startDrop = invItemTarget;
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
}

void Apples::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasText())
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
        event->ignore();
}

void Apples::dragMoveEvent(QDragMoveEvent * event){}


void Apples::dropEvent(QDropEvent *event)
{
    QTableWidgetItem *targetItem = itemAt(event->pos());

    InventoryItem *invItemTarget  = (InventoryItem*)targetItem;
    endDrop = invItemTarget;
    if(startDrop != endDrop)
    {
        invItemTarget->increaseCount(event->mimeData()->text().toInt());

        invItemTarget->setIcon_();
        invItemTarget->setText(QString::number(invItemTarget->getCount()));
        event->acceptProposedAction();
    }
    else
        event->ignore();



}
