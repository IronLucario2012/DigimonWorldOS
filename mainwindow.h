#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void welcomeMessage();
    void enterRoom();
    Game *game;

private slots:
    void on_goNorthButton_released();

    void on_goWestButton_released();

    void on_goEastButton_released();

    void on_goSouthButton_released();

    void on_itemsOnGround_doubleClicked(const QModelIndex &index);

    void on_inventory_doubleClicked(const QModelIndex &index);

    void on_Ranged_released();

    void on_Heavy_released();

    void on_Light_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
