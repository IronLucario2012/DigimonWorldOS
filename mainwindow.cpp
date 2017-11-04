#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->welcomeMessage();
    //this->enterRoom();
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
    enterRoom();
}

void MainWindow::on_goWestButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("west")));
    enterRoom();
}

void MainWindow::on_goEastButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("east")));
    enterRoom();
}

void MainWindow::on_goSouthButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("south")));
    enterRoom();
}

void MainWindow::on_itemsOnGround_doubleClicked(const QModelIndex &index)
{
    ui->inventory->addItem(ui->itemsOnGround->takeItem(index.row()));
    game->currentRoom->takeItem(ui->inventory->item(ui->inventory->count()-1)->text().toStdString());
}

void MainWindow::on_inventory_doubleClicked(const QModelIndex &index)
{
    ui->itemsOnGround->addItem(ui->inventory->takeItem(index.row()));
    game->currentRoom->addItem(new Item(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString()));
}

void MainWindow::enterRoom()
{
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
    if(game->currentRoom->hasEnemy())
        ui->combat_tab->setVisible(true);
    else
        ui->combat_tab->setVisible(false);
    QStringList item;
    vector<string> items = game->currentRoom->displayItems();
    for(int i=0;i<items.size();i++)
    {
        string temp = items[i];
        item << QString::fromStdString(temp);
    }
    while(ui->itemsOnGround->count()>0)
    {
      ui->itemsOnGround->takeItem(0);
    }
    ui->itemsOnGround->addItems(item);
}

void MainWindow::on_Ranged_released()
{

}

void MainWindow::on_Heavy_released()
{

}

void MainWindow::on_Light_released()
{

}
