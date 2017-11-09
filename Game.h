#ifndef GAME_H_
#define GAME_H_

#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;

class Game {
private:

    Digimon* player;
    Room* currentRoom;
    vector<Room*> roomList;
    vector<Item*> inventory;
    void createRooms();
    void createItems();
    void displayItems();

public:

    Game();
    bool checkInventoryForKey();
    string go(string direction);
    string showMap();
    string getCurrentRoomDescription();
    Digimon* getPlayer();
    Room* getCurrentRoom();
    vector<Item*>* getInventory();
};

#endif /*GAME_H_*/
