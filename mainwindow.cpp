#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //create data base
    dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite
    dbase->open("db_playEquipment.sqlite");// if the file does not exists, create with that name
    dbase->createTables();

    ui->setupUi(this);

    connect(ui->apples, SIGNAL(externalItem()), ui->inventory, SLOT(changeExternalItemValue()));
    InventoryItem *originItem = new InventoryItem();
    originItem->setCount(1);
    originItem->setIcon_();
    for(int i = 1; i <= ui->inventory->rowCount()*ui->inventory->columnCount(); i++)
    {
        dbase->insertIntoEquipment(i, originItem->getItemType(), 0);
    }
    ui->apples->setItem(0,0,originItem);


    animation = new QPropertyAnimation(ui->slidingMenu, "geometry");

    //create data base
    //    QStringList tables = dbase->getListTables();
    //    qDebug() <<"List of tables: " <<tables;
    //    QStringList items = dbase->getItems();
    //    qDebug() <<"List of items: " << items;
    //    QStringList inventory = dbase->getEquipment();
    //    qDebug() <<"List of equipment: " << inventory;
}

MainWindow::~MainWindow()
{
    //    QStringList tables = dbase->getListTables();
    //    qDebug() <<"List of tables: " <<tables;
    //    QStringList items = dbase->getItems();
    //    qDebug() <<"List of items: " << items;
    //    QStringList inventory = dbase->getEquipment();
    //    qDebug() <<"List of equipment: " << inventory;

    delete ui;
    dbase->eraseEquipment();
    dbase->eraseItems();
}

void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_start_clicked()
{
    ui->inventory->setEnabled(true);
    ui->apples->setEnabled(true);

    animation->setDuration(3000);
    animation->setStartValue(QRect(0, 0, 100, 30));
    animation->setEndValue(QRect(0, -50, 100, 30));

    animation->start();

    Inventory *inv = new Inventory();
    for(int row = 0; row < ui->inventory->rowCount(); row++)
    {
        for(int col = 0; col < ui->inventory->columnCount(); col++)
        {
            ui->inventory->setItem(row, col, new InventoryItem());
        }
    }
}

void MainWindow::on_outSlidingMenu_clicked()
{
    animation->setDuration(3000);
    animation->setStartValue(QRect(0, -50, 100, 30));
    animation->setEndValue(QRect(0, 0, 100, 30));
    animation->start();
    ui->inventory->setEnabled(false);
    ui->apples->setEnabled(false);

}
