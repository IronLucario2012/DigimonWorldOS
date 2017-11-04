#ifndef GAME_H_
#define GAME_H_

#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class Game {
private:

    vector<Room*> roomList;
    vector<Item*> inventory;
    void createRooms();
    void createItems();
    void displayItems();
    string printInventory();

public:
    Game();
    Room *currentRoom;
    string go(string direction);
    string showMap();
    string getCurrentRoomDescription();
    string pickUp(string name);
};

#endif /*GAME_H_*/
