#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db_manager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int row = 0; row < ui->inventory->rowCount(); row++)
    {
        for(int col = 0; col < ui->inventory->columnCount(); col++)
        {
            ui->inventory->setItem(row, col, new InventoryItem());
        }
    }

    ui->apples->setItem(0,0, new InventoryItem());

    InventoryItem *originItem = new InventoryItem();
    originItem->setCount(1);
    originItem->setIcon_();
    ui->apples->setItem(0,0,originItem);


    animation = new QPropertyAnimation(ui->slidingMenu, "geometry");
    //пример работы с БД
    DB_Manager* dbase = new DB_Manager(); //создание БД по умолчанию db_playEquipment.sqlite
    QStringList tables = dbase->getListTables(); //получение списка существующих таблиц (должно быть 3 "equipment", "items", "sqlite_sequence")
    dbase->createTables(); //если (БД удалялась и) какой то из "equipment", "items" не хватает, создать их
    dbase->insertIntoItems("apple","pic1.jpg"); //добавление элемента в таблицу Items
    dbase->insertIntoEquipment(2,1,5); //добавление элемента в таблицу Equipment
    dbase->insertIntoItems("orange","pic2,png");
    //dbase->deleteFromItems("orange"); //удаление из Items
    QStringList items = dbase->getAllItems(); //получение всего списка таблиц
    qDebug() << items;

    //конец


}

MainWindow::~MainWindow()
{
    delete ui;
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
