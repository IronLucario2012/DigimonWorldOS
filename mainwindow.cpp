#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->welcomeMessage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::welcomeMessage()
{
    ui->textOutput->setText(QString::fromStdString(game->getCurrentRoomDescription()));
}

void MainWindow::on_goNorthButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("north")));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
}

void MainWindow::on_goWestButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("west")));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
}

void MainWindow::on_goEastButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("east")));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
}

void MainWindow::on_goSouthButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("south")));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
}

void MainWindow::on_itemsOnGround_doubleClicked(const QModelIndex &index)
{

}

void MainWindow::on_inventory_doubleClicked(const QModelIndex &index)
{

}
