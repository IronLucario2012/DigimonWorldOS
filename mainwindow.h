#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include "Game.h"
#include "gameoverwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void startMessage();
    void updateUI();
    void fightResults(string out);
    void gameOver(int victory);
    void setGame(Game* temp);
    void addTextToOutput(string add);

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
    Game *game;
    string log;
};

#endif // MAINWINDOW_H
