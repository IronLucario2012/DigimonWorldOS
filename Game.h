#ifndef GAME_H_
#define GAME_H_

#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class Game {
private:
	Room *currentRoom;
    vector<Room*> roomList;
    vector<Item*> inventory;

    void createRooms();
    void createItems();
    void displayItems();
    string printInventory();

public:
    Game();
	string go(string direction);
    //string teleport();
    string showMap();
    string getCurrentRoomDescription();
    string pickUp(string name);
};

#endif /*GAME_H_*/
