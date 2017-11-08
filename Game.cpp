#include <iostream>
#include <QApplication>

using namespace std;
#include "Game.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game temp;
    MainWindow w;
    w.game = &temp;
    w.show();
    w.startMessage();
    return a.exec();
}

Game::Game()
{
    createRooms();
}

void Game::createRooms()
{
    string roomPath = "../DigimonWorldOS/img/room";
    string digimonPath = "../DigimonWorldOS/img/digimon";


    Room *a, *b, *c, *d, *e, *f, *g, *h, *i;

    player = new Digimon(2,1,"Hackmon",20,"");

    a = new Room("a",roomPath+"/a.jpg");
        a->addItem(new Item("boss key"));
    roomList.push_back(a);
    b = new Room("b",roomPath+"/b.jpg");
    roomList.push_back(b);
    c = new Room("c",roomPath+"/c.jpg");
        c->setEnemy(new Digimon(2,2,"Tsukaimon",10,digimonPath+"/Tsukaimon.png"));
    roomList.push_back(c);
    d = new Room("d",roomPath+"/d.jpg");
        d->setEnemy(new Digimon(2,2,"Gazimon",15,digimonPath+"/Gazimon.png"));
    roomList.push_back(d);
    e = new Room("e",roomPath+"/e.jpg");
    roomList.push_back(e);
    f = new Room("f",roomPath+"/f.png");
    roomList.push_back(f);
    g = new Room("g",roomPath+"/g.png");
        g->setEnemy(new Digimon(2,0,"Renamon",10,digimonPath+"/Renamon.png"));
    roomList.push_back(g);
    h = new Room("h",roomPath+"/h.jpg", true);
        h->setEnemy(new Digimon(3,2,"Youkomon",30,digimonPath+"/Youkomon.png"));
    roomList.push_back(h);
    i = new Room("i",roomPath+"/i.jpg");
    roomList.push_back(i);

//             (N,    E,    S,    W)
    a->setExits(NULL, b,    d,    NULL);
    b->setExits(g   , NULL, e,    a);
    c->setExits(NULL, NULL, i,    NULL);
    d->setExits(a,    e,    NULL, i);
    e->setExits(b,    NULL, NULL, d);
    f->setExits(NULL, g,    NULL, h);
    g->setExits(NULL, NULL, b,    f);
    h->setExits(NULL, f,    NULL, NULL);
    i->setExits(c   , d,    NULL, NULL);

    currentRoom = i;
}

string Game::printInventory()
{
    string out="";
    int size = inventory.size();
    for(int i=0;i<size;i++)
        out += inventory.at(i)->getName() + "\n";
    if (out=="")
        out = "No items in inventory";
    return out;
}

string Game::go(string direction)
{
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
        return(currentRoom->longDescription() + "\ndirection null");
	else
	{
        if(nextRoom->boss&&!checkInventoryForKey())
        {
            return ""+currentRoom->longDescription()+"\nThe door to room h is locked. You need a key.";
        }
        else
        {
            currentRoom = nextRoom;
            return currentRoom->longDescription();
        }
	}
}

bool Game::checkInventoryForKey()
{
    bool found = false;
    for(size_t i=0;i<inventory.size()&&!found;i++)
    {
        if(inventory[i]->getName().compare("boss key")==0)
            found=true;
    }
    return found;
}

string Game::showMap()
{
    string map = "";
    map += "[h] -|- [f] --- [g]\n";
    map += "                 | \n";
    map += "                 | \n";
    map += "[c]     [a] --- [b]\n";
    map += " |       |       | \n";
    map += " |       |       | \n";
    map += "[i] --- [d] --- [e]\n";
return map;
}

string Game::getCurrentRoomDescription()
{
    return currentRoom->longDescription();
}
