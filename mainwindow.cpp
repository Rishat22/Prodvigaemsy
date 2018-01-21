#include "mainwindow.h"
#include "ui_mainwindow.h"

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
