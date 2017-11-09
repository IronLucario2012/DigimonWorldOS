#include "Room.h"

Room::Room(string description, string imgPath, bool bossRoom)//Constructor
{
    this->name = description;
    this->boss = bossRoom;
    this->imgPath = imgPath;
    this->inRoom = vector<Digimon>(0);
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)//Sets which rooms can be reached from this one
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

bool Room::hasExit(string direction)//Returns whether a room can be reached in the given direction
{
    return (exits[direction] != NULL);
}

string Room::shortDescription()//Returns the room's name
{
    return name;
}

string Room::longDescription()//Returns the room's name and any enemy in it with a short message
{
    return "You are in room " + name + ".\n" + enemyString();
}

string Room::enemyString()//Returns the enemy present and their HP
{
    string out = "";
    if(hasEnemy())
    {
        out += "Enemy digimon present:\n";
        out += getEnemy().getName() + " - HP: ";
        out += getEnemy().getHPString() + "\n";
    }
    return out;
}

Room* Room::nextRoom(string direction)
{
	map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}

void Room::addItem(Item *inItem)//Adds the given item to the room
{
    itemsInRoom.push_back(*inItem);
}

void Room::setEnemy(Digimon *newEn)//Adds the given enemy to the room
{
    inRoom.push_back(*newEn);
}
bool Room::hasEnemy()//Returns whether the room has an enemy
{
    bool out = false;
    if(inRoom.size()>0)
        out = true;
    return out;
}
void Room::removeEnemy()//Removes the enemy from the room
{
    inRoom.pop_back();
}
vector<string> Room::displayItems()//returns a string vector of the items in the room
{
    vector<string> items;

    for(size_t i=0;i<itemsInRoom.size();i++)
        items.push_back(itemsInRoom[i].getName());
    return items;
}

int Room::numberOfItems()//Returns the number of items in the room
{
    return itemsInRoom.size();
}

int Room::takeItem(string inString)//Removes an item from the room
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

void Room::setPix(string pix)//Sets the room's image
{
   imgPath = pix;
}
QPixmap Room::getPix()//Returns the room's image at the correct size
{
   QPixmap roomPix(QString::fromStdString(imgPath));
   QPixmap finalRoomPix = roomPix.scaled(QSize(400,400), Qt::KeepAspectRatio);
   return finalRoomPix;
}

Digimon Room::getEnemy()//Returns the enemy in the room
{
    return inRoom.at(0);
}

Digimon* Room::getEnemyPointer()//Returns a pointer to the enemy in the room
{
    return &inRoom[0];
}

bool Room::isBoss()//Returns whether or not the room is a boss room
{
    return boss;
}
