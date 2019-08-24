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

void MainWindow::setGame(Game* temp)//Sets the game the window will interact with
{
    game = temp;
}

void MainWindow::on_goNorthButton_released()//Moves the player one room north
{
    addTextToOutput(game->go("north"));
    updateUI();
}

void MainWindow::on_goWestButton_released()//Moves the player one room  west
{
    addTextToOutput(game->go("west"));
    updateUI();
}

void MainWindow::on_goEastButton_released()//Moves the player one room east
{
    addTextToOutput(game->go("east"));
    updateUI();
}

void MainWindow::on_goSouthButton_released()//Moves the player one room south
{
    addTextToOutput(game->go("south"));
    updateUI();
}

void MainWindow::on_itemsOnGround_doubleClicked(const QModelIndex &index)//Takes the clicked item from the ground and puts it in the inventory
{
    ui->inventory->addItem(ui->itemsOnGround->takeItem(index.row()));
    game->getCurrentRoom()->takeItem(ui->inventory->item(ui->inventory->count()-1)->text().toStdString());
    game->getInventory()->push_back(new Item(ui->inventory->item(ui->inventory->count()-1)->text().toStdString()));
}

void MainWindow::on_inventory_doubleClicked(const QModelIndex &index)//Takes the clicked item from the inventory and puts it on the ground
{
    ui->itemsOnGround->addItem(ui->inventory->takeItem(index.row()));
    game->getCurrentRoom()->addItem(new Item(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString()));
    int indexInv = -1;
    for(size_t i=0;i<game->getInventory()->size();i++)
    {
        if(game->getInventory()->at(i)->getName().compare(ui->itemsOnGround->item(ui->itemsOnGround->count()-1)->text().toStdString())==0)
            indexInv = static_cast<int>(i);
    }
    if(indexInv>=0)
        game->getInventory()->erase(game->getInventory()->begin() + indexInv);
}

void MainWindow::startMessage()//Displays the first message and the map and sets the enemy images to have translucent backgrounds
{
    ui->textOutput->setText(QString::fromStdString("You are Hackmon, a Digimon aiming to join the ranks of the Royal Knights.\nAs a first test, they have sent you to clear out a small dungeon of hostile Digimon.\nThey are feral, so their attacks will be effectively random.\nEven so, do not underestimate them.\nThe Digimon keeping them there is a Champion level.\nYou will likely need to Digivolve to that level yourself in order to stand a chance.\n(Digivolving to the Champion level takes 3 xp.)\n\nGood luck."));
    ui->floorMap->setText(QString::fromStdString(game->showMap()));
    ui->enemyImageC->setAttribute(Qt::WA_TranslucentBackground);
    updateUI();
}

void MainWindow::updateUI()//Updates the UI
{
    string colours[]{"blue","green","red"};

    //Sets the Current Room, HP, and XP bars
    ui->hpDisplay->setText(QString::fromStdString("HP: "+game->getPlayer()->getHPString()));
    ui->hpDisplayC->setText(QString::fromStdString("HP: "+game->getPlayer()->getHPString()));
    ui->xpDisplay->setText(QString::fromStdString("XP: " + to_string(game->getPlayer()->getXP()) + "/3"));
    ui->roomDisplay->setText(QString::fromStdString("Current Room: " + game->getCurrentRoom()->shortDescription()));

    //Enables or disables the direction buttons depending on whether there's a room in that direction
    ui->goEastButton->setEnabled(game->getCurrentRoom()->hasExit("east"));
    ui->goWestButton->setEnabled(game->getCurrentRoom()->hasExit("west"));
    ui->goNorthButton->setEnabled(game->getCurrentRoom()->hasExit("north"));
    ui->goSouthButton->setEnabled(game->getCurrentRoom()->hasExit("south"));

    //Checks whether there is an enemy in the room and updates the UI based on that
    if(game->getCurrentRoom()->hasEnemy())
    {
        ui->tabs->setCurrentIndex(1);//Go to and enable combat tab, disable map tab, display enemy information
        ui->tabs->setTabEnabled(0,false);
        ui->tabs->setTabEnabled(1,true);
        ui->textOutputC->setText(QString::fromStdString(game->getCurrentRoom()->enemyString()));
        ui->attributeAdvantageC->setStyleSheet(QString::fromStdString("QLabel { background-color : " + colours[game->getPlayer()->rockPaperScissors(game->getPlayer()->getAttribute(),game->getCurrentRoom()->getEnemy().getAttribute())] + "; }"));
        ui->levelAdvantageC->setStyleSheet(QString::fromStdString("QLabel { background-color : " + colours[game->getPlayer()->levelCompare(game->getCurrentRoom()->getEnemy().getLevel())] + "; }"));
    }
    else
    {
        ui->tabs->setCurrentIndex(0);//Go to and enable map tab, disable combat tab
        ui->tabs->setTabEnabled(0,true);
        ui->tabs->setTabEnabled(1,false);
    }
    //Get the items from the current room and put them in a QStringList
    QStringList item;
    vector<string> items = game->getCurrentRoom()->displayItems();

    for(size_t i=0;i<items.size();i++)
    {
        string temp = items[i];
        item << QString::fromStdString(temp);
    }
    //Remove the items on the ground in the last room from the UI
    while(ui->itemsOnGround->count()>0)
    {
      ui->itemsOnGround->takeItem(0);
    }
    //Show the items on the ground in the current room
    ui->itemsOnGround->addItems(item);

    //Show the images for the current room and, if present, the enemy
    ui->roomImage->setPixmap(game->getCurrentRoom()->getPix());
    if(game->getCurrentRoom()->hasEnemy())
    {
        ui->enemyImageC->setVisible(true);
        ui->enemyImageC->setPixmap(game->getCurrentRoom()->getEnemy().getPix());
        ui->roomImageC->setPixmap(game->getCurrentRoom()->getPix());
    }
    else
    {
        ui->enemyImageC->setVisible(false);
    }
}

void MainWindow::on_Heavy_released()//The player has used a Heavy attack
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),0);
    fightResults(out);
}

void MainWindow::on_Light_released()//The player has used a Light attack
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),1);
    fightResults(out);
}

void MainWindow::on_Ranged_released()//The player has used a Ranged attack
{
    string out = game->getPlayer()->fight(game->getCurrentRoom()->getEnemyPointer(),2);
    fightResults(out);
}

void MainWindow::fightResults(string out)//Interpret and act on the results of a round of combat
{
    if(out.back()=='n')//If the fight ended with a player win, remove the enemy, give the player XP,
                       //display a message, and if it was a boss, end the game with a victory
    {
        game->getCurrentRoom()->removeEnemy();
        addTextToOutput(out + ".\n"+ game->getPlayer()->addXP() + game->getCurrentRoom()->longDescription());
        updateUI();
        if(game->getCurrentRoom()->isBoss())
            gameOver(0);
    }
    else if(out.back()=='.')//If the fight isn't over, refresh the UI with the new stats
    {
        updateUI();
        ui->textOutputC->setText(QString::fromStdString(out));
    }
    else//If neither of the above apply, the player is dead and the game ends in a loss
    {
        ui->textOutputC->setText(QString::fromStdString(out+"."));
        gameOver(1);
    }
}

void MainWindow::gameOver(int victory)//Shows the game over window with an appropriate message based on the number passed in
{
    GameOverWindow w;
    w.show();
    w.setMessage(victory);
    w.exec();
}

void MainWindow::addTextToOutput(string add)//Append the new string to the text log with a line break
{
    log = ui->textOutput->toPlainText().toStdString();
    ui->textOutput->setText(QString::fromStdString(log+"\n~~~~~\n"+add));
    QScrollBar *sb = ui->textOutput->verticalScrollBar();
    sb->setValue(sb->maximum());
}
