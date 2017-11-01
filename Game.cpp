#include <iostream>
#include <QApplication>

using namespace std;
#include "Game.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Game temp;
    MainWindow w;
    w.game = &temp;
    w.show();
    w.welcomeMessage();
    return a.exec();
}

Game::Game() {
	createRooms();
}

void Game::createRooms()  {

    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *t;

    a = new Room("a");
        a->addItem(new Item("key"));
    roomList.push_back(a);
    b = new Room("b");
    roomList.push_back(b);
	c = new Room("c");
    roomList.push_back(c);
	d = new Room("d");
    roomList.push_back(d);
	e = new Room("e");
    roomList.push_back(e);
	f = new Room("f");
    roomList.push_back(f);
	g = new Room("g");
    roomList.push_back(g);
	h = new Room("h");
    roomList.push_back(h);
	i = new Room("i");
    roomList.push_back(i);
    t = new Room("t");
    roomList.push_back(t);

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
    t->setExits(NULL, NULL, NULL, NULL);

    currentRoom = i;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
 /*bool Game::processCommand(Command command) {

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {
   if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
}*/
/** COMMANDS **/

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

/*string Game::teleport() {

    int destination = rand() %roomList.size();

    currentRoom = roomList[destination];

    return currentRoom->longDescription();
}*/

string Game::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
        return(currentRoom->longDescription() + "\ndirection null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}

string Game::showMap()
{
    string map = "";
    map += "[h] --- [f] --- [g]\n";
    map += "                 | \n";
    map += "                 | \n";
    map += "[c]     [a] --- [b]\n";
    map += " |       |       | \n";
    map += " |       |       | \n";
    map += "[i] --- [d] --- [e]\n";
    map += "                   \n";
    map += "                   \n";
    map += "        [t]        \n";
return map;
}

string Game::getCurrentRoomDescription()
{
    return currentRoom->longDescription();
}

string Game::pickUp(string name)
{








    return "You picked up the " + name;
}














