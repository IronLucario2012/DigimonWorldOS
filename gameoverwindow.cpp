#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

GameOverWindow::GameOverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);
}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}

void GameOverWindow::on_OKButton_released()
{
    exit(EXIT_SUCCESS);
}

void GameOverWindow::setMessage(int vic)
{
    if(vic==0)
        ui->gameOverMessage->setText(QString::fromStdString("Game Over!\nYou Won!"));
    else
        ui->gameOverMessage->setText(QString::fromStdString("Game Over!\nYou Died!"));
}
