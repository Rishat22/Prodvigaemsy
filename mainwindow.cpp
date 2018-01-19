#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    obj = new QSound("cutApple.wav");
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


    obj->play();
}
