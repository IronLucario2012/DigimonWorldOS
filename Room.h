#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "Digimon.h"
#include <QtGui>
using namespace std;
using std::vector;

class Room {

private:
	string description;
    string imgPath;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;


public:
    vector<Digimon> inRoom;
    Room(string description, string imgPath="", bool bossRoom=false);
    bool boss;
    string enemyString();
    string itemsToString();
    int numberOfItems();
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void setEnemy(Digimon *newEn);
    bool hasEnemy();
    Digimon getEnemy();
    Digimon* getEnemyPointer();
    void removeEnemy();
    vector<string> displayItems();
    int takeItem(string inString);
    void removeItemFromRoom(int location);
    void setPix(string pix);
    QPixmap getPix();
};

#endif
