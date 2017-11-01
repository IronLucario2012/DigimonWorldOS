#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "item.h"
#include "Enemy.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;

public:
    vector <Enemy*> enemiesInRoom;
    string itemsToString();
    int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    void setEnemy(Enemy *newEn);
    void setEnemy(int level, int attribute, string name, int hp);
    bool hasEnemy();
    vector<string> displayItems();
    int isItemInRoom(string inString);
    void removeItemFromRoom(int location);
};

#endif
