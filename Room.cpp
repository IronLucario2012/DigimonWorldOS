#include "Room.h"

Room::Room(string description, bool bossRoom)
{
	this->description = description;
    this->boss = bossRoom;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
	if (north != NULL)
		exits["north"] = north;
	if (east != NULL)
		exits["east"] = east;
	if (south != NULL)
		exits["south"] = south;
	if (west != NULL)
		exits["west"] = west;
}

string Room::shortDescription()
{
	return description;
}

string Room::longDescription()
{
    return "You are in room " + description + ".\n" + exitString();
}

string Room::exitString()
{
    string returnString = "There are exits to the";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end();i++)
    {
		// Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    }
	return returnString;
}

Room* Room::nextRoom(string direction)
{
	map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem)
{
    itemsInRoom.push_back(*inItem);
}

void Room::setEnemy(Enemy *newEn)
{
    enemiesInRoom.push_back(newEn);
}

bool Room::hasEnemy()
{
    bool out = false;
    if(enemiesInRoom.size()>0)
        out = true;
    return out;
}

void Room::setEnemy(int level, int attribute, string name, int hp)
{
    enemiesInRoom.push_back(new Enemy(level, attribute, name, hp));
}

vector<string> Room::displayItems()
{
    vector<string> items;

    for(int i=0;i<itemsInRoom.size();i++)
        items.push_back(itemsInRoom[i].getName());
    return items;
}

string Room::itemsToString()
{
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if(sizeItems<1)
        tempString = "No items in room.";
    else
        if(sizeItems>0)
        {
            int x = 0;
            for(int i=sizeItems;i>0;i--)
            {
                tempString += itemsInRoom[x].getName() + " ";
                x++;
            }
        }
    return tempString;
}

int Room::numberOfItems()
{
    return itemsInRoom.size();
}

int Room::takeItem(string inString)
{
    int sizeItems = (itemsInRoom.size());
       int x = (0);
        for (int n = sizeItems; n > 0; n--)
        {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getName());
            if (tempFlag == 0)
            {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
        }
    return -1;
}

