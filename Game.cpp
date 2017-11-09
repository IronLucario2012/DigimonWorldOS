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
    w.setGame(&temp);
    w.show();
    w.startMessage();
    return a.exec();
}

Game::Game()//Default constructor
{
    createRooms();
}

void Game::createRooms()//Setting up the game
{
    string roomPath = "../DigimonWorldOS/img/room";
    string digimonPath = "../DigimonWorldOS/img/digimon";


    Room *a, *b, *c, *d, *e, *f, *g, *h, *i;

    player = new Digimon(2,1,"Hackmon",20,"");//Making the player

    //Creating the maze and populating it with enemies and items

    a = new Room("a",roomPath+"/a.jpg");
        a->addItem(new Item("boss key"));
        a->setEnemy(new Digimon(2,2,"Gazimon",15,digimonPath+"/Gazimon.png"));
    roomList.push_back(a);
    b = new Room("b",roomPath+"/b.jpg");
    roomList.push_back(b);
    c = new Room("c",roomPath+"/c.jpg");
        c->setEnemy(new Digimon(2,2,"Tsukaimon",10,digimonPath+"/Tsukaimon.png"));
    roomList.push_back(c);
    d = new Room("d",roomPath+"/d.jpg");
    roomList.push_back(d);
    e = new Room("e",roomPath+"/e.jpg");
        e->setEnemy(new Digimon(2,0,"Renamon",10,digimonPath+"/Renamon.png"));
    roomList.push_back(e);
    f = new Room("f",roomPath+"/f.png");
    roomList.push_back(f);
    g = new Room("g",roomPath+"/g.png");
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

    currentRoom = i;//Setting the starting location
}

string Game::go(string direction)
{
    //If the door isn't locked or you have a key, move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
    string out = "";
    if(nextRoom->isBoss()&&!checkInventoryForKey())
    {
        out = currentRoom->longDescription()+"\nThe door to room h is locked. You need a key.";
    }
    else
    {
        currentRoom = nextRoom;
        out = currentRoom->longDescription();
    }
    return out;
}

bool Game::checkInventoryForKey()//Checks if the inventory contains a key
{
    bool found = false;
    for(size_t i=0;i<inventory.size()&&!found;i++)
    {
        if(inventory[i]->getName().compare("boss key")==0)
            found=true;
    }
    return found;
}

string Game::showMap()//Returns a string that shows the map of this floor
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

string Game::getCurrentRoomDescription()//Returns the description of the current room
{
    return currentRoom->longDescription();
}

Digimon* Game::getPlayer()//Returns a pointer to the player
{
    return player;
}

Room* Game::getCurrentRoom()//Returns a pointer to the current room
{
    return currentRoom;
}

vector<Item*>* Game::getInventory()//Returns a pointer to the inventory vector
{
    vector<Item*> *inv = &inventory;
    return inv;
}
