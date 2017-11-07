#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    game->inventory.push_back(new Item(ui->inventory->item(ui->inventory->count()-1)->text().toStdString()));
}

void MainWindow::on_inventory_doubleClicked(const QModelIndex &index)
{
    ui->itemsOnGround->addItem(ui->inventory->takeItem(index.row()));
    game->currentRoom->addItem(new Item(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString()));
    int indexInv = -1;
    for(int i=0;i<game->inventory.size();i++)
    {
        if(game->inventory[i]->getName().compare(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString())==0)
            indexInv = i;
    }
    if(indexInv>=0)
        game->inventory.erase(game->inventory.begin() + indexInv);
}

void MainWindow::startMessage()
{
    ui->textOutput->setText(QString::fromStdString(game->currentRoom->longDescription()));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
    enterRoom();
}

void MainWindow::enterRoom()
{
    if(game->currentRoom->hasEnemy())
    {
        ui->tabs->setCurrentIndex(1);
        ui->tabs->setTabEnabled(0,false);
        ui->tabs->setTabEnabled(1,true);
        ui->textOutputC->setText(QString::fromStdString(game->currentRoom->enemyString()));
    }
    else
    {
        ui->tabs->setCurrentIndex(0);
        ui->tabs->setTabEnabled(0,true);
        ui->tabs->setTabEnabled(1,false);
    }
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

    ui->roomImage->setPixmap(game->currentRoom->getPix());
    ui->roomImageC->setPixmap(game->currentRoom->getPix());
    if(game->currentRoom->hasEnemy())
    {
        ui->enemyImageC->setVisible(true);
        ui->enemyImageC->setPixmap(game->currentRoom->getEnemy().getPix());
    }
    else
    {
        ui->enemyImageC->setVisible(false);
    }
}

void MainWindow::on_Heavy_released()
{
    string out = game->player->fight(game->currentRoom->getEnemy(),0);
    if(out.back()=='n')
    {
        game->currentRoom->removeEnemy();
        ui->textOutput->setText(QString::fromStdString(out + "\n" + game->currentRoom->longDescription()));
        enterRoom();
    }
    else if(out.back()=='.')
    {
        enterRoom();
        ui->textOutputC->setText(QString::fromStdString(out) + "\n" + ui->textOutputC->text());
    }
    else
    {
        //TODO: Game over.
        ui->textOutputC->setText(QString::fromStdString(out));
    }
}

void MainWindow::on_Light_released()
{
    string out = game->player->fight(game->currentRoom->getEnemy(),1);
    if(out.back()=='n')
    {
        game->currentRoom->removeEnemy();
        ui->textOutput->setText(QString::fromStdString(out + "\n" + game->currentRoom->longDescription()));
        enterRoom();
    }
    else if(out.back()=='.')
    {
        enterRoom();
        ui->textOutputC->setText(QString::fromStdString(out) + "\n" + ui->textOutputC->text());
    }
    else
    {
        //TODO: Game over.
        ui->textOutputC->setText(QString::fromStdString(out));
    }
}

void MainWindow::on_Ranged_released()
{
    string out = game->player->fight(game->currentRoom->getEnemy(),2);
    if(out.back()=='n')
    {
        game->currentRoom->removeEnemy();
        ui->textOutput->setText(QString::fromStdString(out + "\n" + game->currentRoom->longDescription()));
        enterRoom();
    }
    else if(out.back()=='.')
    {
        enterRoom();
        ui->textOutputC->setText(QString::fromStdString(out) + "\n" + ui->textOutputC->text());
    }
    else
    {
        //TODO: Game over.
        ui->textOutputC->setText(QString::fromStdString(out));
    }
}

void MainWindow::on_debugCombatWin_released()
{
    game->currentRoom->removeEnemy();
    ui->textOutput->setText(QString::fromStdString(game->currentRoom->longDescription()));
    enterRoom();
}
