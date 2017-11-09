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

void MainWindow::setGame(Game* temp)
{
    game = temp;
}

void MainWindow::on_goNorthButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("north")));
    updateUI();
}

void MainWindow::on_goWestButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("west")));
    updateUI();
}

void MainWindow::on_goEastButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("east")));
    updateUI();
}

void MainWindow::on_goSouthButton_released()
{
    ui->textOutput->setText(QString::fromStdString(game->go("south")));
    updateUI();
}

void MainWindow::on_itemsOnGround_doubleClicked(const QModelIndex &index)
{
    ui->inventory->addItem(ui->itemsOnGround->takeItem(index.row()));
    game->getCurrentRoom()->takeItem(ui->inventory->item(ui->inventory->count()-1)->text().toStdString());
    game->getInventory()->push_back(new Item(ui->inventory->item(ui->inventory->count()-1)->text().toStdString()));
}

void MainWindow::on_inventory_doubleClicked(const QModelIndex &index)
{
    ui->itemsOnGround->addItem(ui->inventory->takeItem(index.row()));
    game->getCurrentRoom()->addItem(new Item(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString()));
    int indexInv = -1;
    for(size_t i=0;i<game->getInventory()->size();i++)
    {
        if(game->getInventory()->at(i)->getName().compare(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString())==0)
            indexInv = i;
    }
    if(indexInv>=0)
        game->getInventory()->erase(game->getInventory()->begin() + indexInv);
}

void MainWindow::startMessage()
{
    ui->textOutput->setText(QString::fromStdString(game->getCurrentRoom()->longDescription()));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
    ui->enemyImageC->setAttribute(Qt::WA_TranslucentBackground);
    updateUI();
}

void MainWindow::updateUI()
{
    ui->hpDisplay->setText(QString::fromStdString("HP: "+game->getPlayer()->getHPString()));
    ui->hpDisplayC->setText(QString::fromStdString("HP: "+game->getPlayer()->getHPString()));
    if(game->getCurrentRoom()->hasEnemy())
    {
        ui->tabs->setCurrentIndex(1);
        ui->tabs->setTabEnabled(0,false);
        ui->tabs->setTabEnabled(1,true);
        ui->textOutputC->setText(QString::fromStdString(game->getCurrentRoom()->enemyString()));
    }
    else
    {
        ui->tabs->setCurrentIndex(0);
        ui->tabs->setTabEnabled(0,true);
        ui->tabs->setTabEnabled(1,false);
    }
    QStringList item;
    vector<string> items = game->getCurrentRoom()->displayItems();
    for(size_t i=0;i<items.size();i++)
    {
        string temp = items[i];
        item << QString::fromStdString(temp);
    }
    while(ui->itemsOnGround->count()>0)
    {
      ui->itemsOnGround->takeItem(0);
    }
    ui->itemsOnGround->addItems(item);

    ui->roomImage->setPixmap(game->getCurrentRoom()->getPix());
    ui->roomImageC->setPixmap(game->getCurrentRoom()->getPix());
    if(game->getCurrentRoom()->hasEnemy())
    {
        ui->enemyImageC->setVisible(true);
        ui->enemyImageC->setPixmap(game->getCurrentRoom()->getEnemy().getPix());
    }
    else
    {
        ui->enemyImageC->setVisible(false);
    }
}

void MainWindow::on_Heavy_released()
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),0);
    fightResults(out);
}

void MainWindow::on_Light_released()
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),1);
    fightResults(out);
}

void MainWindow::on_Ranged_released()
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),2);
    fightResults(out);
}

void MainWindow::fightResults(string out)
{
    if(out.back()=='n')
    {
        game->getCurrentRoom()->removeEnemy();
        ui->textOutput->setText(QString::fromStdString(out + ".\n"+ game->getPlayer()->addXP() + game->getCurrentRoom()->longDescription()));
        updateUI();
        if(game->getCurrentRoom()->isBoss())
            gameOver(0);
    }
    else if(out.back()=='.')
    {
        updateUI();
        ui->textOutputC->setText(QString::fromStdString(out)/* + "\n" + ui->textOutputC->text()*/);
    }
    else
    {
        ui->textOutputC->setText(QString::fromStdString(out+"."));
        gameOver(1);
    }
}

void MainWindow::gameOver(int victory)
{
    GameOverWindow w;
    w.show();
    w.setMessage(victory);
    w.exec();
}
