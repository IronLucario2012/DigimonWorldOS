#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

GameOverWindow::GameOverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromStdString("Game Over!"));
}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}

void GameOverWindow::on_OKButton_released()
{
    exit(EXIT_SUCCESS);
}

void GameOverWindow::reject()//If the 'X' button is clicked
{
    exit(EXIT_SUCCESS);
}

void GameOverWindow::setMessage(int vic)//Sets the 'game over' message
{
    if(vic==0)
        ui->gameOverMessage->setText(QString::fromStdString("Game Over!\nYou Won!"));
    else
        ui->gameOverMessage->setText(QString::fromStdString("Game Over!\nYou Died!"));
}
