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


    InventoryItem *originItem = new InventoryItem();
    originItem->setCount(1);
    originItem->setIcon_();
    for(int i = 1; i <= ui->inventory->rowCount()*ui->inventory->columnCount(); i++)
    {
        dbase->insertIntoEquipment(i, originItem->getItemType(), 0);
    }
    ui->apples->setItem(0,0,originItem);


    animation = new QPropertyAnimation(ui->slidingMenu, "geometry");
    //пример работы с БД
    /*DB_Manager* dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite
    QStringList tables = dbase->getListTables(); //получение списка существующих таблиц (должно быть 3 "equipment", "items", "sqlite_sequence")
//    dbase->createTables(); //если (БД удалялась и) какой то из "equipment", "items" не хватает, создать их
//    dbase->insertIntoItems("apple","pic1.jpg"); //добавление элемента в таблицу Items
//    dbase->insertIntoEquipment(1,13,5); //добавление элемента в таблицу Equipment
//    dbase->insertIntoEquipment(2,13,4); //добавление элемента в таблицу Equipment
//    dbase->insertIntoItems("orange","pic2,png");
//    //dbase->deleteFromItems("orange"); //удаление из Items
//    QStringList items = dbase->getItems(); //получение всего списка предметов Items
//    items = dbase->getItems("orange"); //получение элементов из Items с name = orange
//    items = dbase->getItems(1); //получения элемента из Items с id = 1
//    dbase->updateItems("apple","pic_apple.png"); // изменения pic по name
//    items = dbase->getItems();
//    dbase->updateItems(14,"potato"); // изменения name по id
//    items = dbase->getItems();
//    dbase->updateItems(14,"orange","pic2.png"); // изменения по id для name и pic
//    items = dbase->getItems();
//    //dbase->eraseItems(); //удаление всех элементов из Items
//    items = dbase->getItems();
//    QStringList inventory = dbase->getEquipment();//получение всего списка equipment
//    inventory = dbase->getEquipment(2); //получения элемента из Equipment с id = 2
//    dbase->updateEquipment(1,7); // изменение count по id
//    inventory = dbase->getEquipment();
//    dbase->updateEquipment(2,"orange",3); //
//    inventory = dbase->getEquipment();
//    dbase->eraseEquipment(); //удаление всех элементов из Equipment
//    inventory = dbase->getEquipment();
//    dbase->insertIntoEquipment(0,"apple",3);
//    inventory = dbase->getEquipment();
//    dbase->insertIntoEquipment(-1,"apple",3);
//    inventory = dbase->getEquipment();
//    dbase->insertIntoEquipment(2,"apple",33);

//    inventory = dbase->getEquipment();
    qDebug() <<"List of tables: " <<tables;
    QStringList items = dbase->getItems();
    qDebug() <<"List of items: " << items;
    QStringList inventory = dbase->getEquipment();
    qDebug() <<"List of equipment: " << items;

    //конец

    //create data base
QStringList tables = dbase->getListTables();
qDebug() <<"List of tables: " <<tables;
    QStringList items = dbase->getItems();
    qDebug() <<"List of items: " << items;
    QStringList inventory = dbase->getEquipment();
    qDebug() <<"List of equipment: " << inventory;
}

MainWindow::~MainWindow()
{
    QStringList tables = dbase->getListTables();
    qDebug() <<"List of tables: " <<tables;
        QStringList items = dbase->getItems();
        qDebug() <<"List of items: " << items;
        QStringList inventory = dbase->getEquipment();
        qDebug() <<"List of equipment: " << inventory;

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
}

void MainWindow::on_outSlidingMenu_clicked()
{
    animation->setDuration(3000);
    animation->setStartValue(QRect(0, -50, 100, 30));
    animation->setEndValue(QRect(0, 0, 100, 30));
    animation->start();

}
