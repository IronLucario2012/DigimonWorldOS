#include "item.h"

Item::Item (string inName)//Constructor
{
    name = inName;
}

string Item::getName()//Returns the name of the item
{
    return name;
}
