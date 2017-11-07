#include "item.h"

Item::Item (string inName, string inDescription)
{
    name = inName;
    description = inDescription;
}

string Item::getName()
{
    return name;
}

string Item::getDescription()
{
    return description;
}
