#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation> //скрытие главного меню
#include <QFile>
#include <QSound> //аудио сопровождение

//вспамогательные библиоеки
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_clicked();

    void on_start_clicked();

    void on_outSlidingMenu_clicked();

private:
    Ui::MainWindow *ui;
    QSound *obj;
    QPropertyAnimation *animation;
};

#endif // MAINWINDOW_H
