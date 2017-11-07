#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string name;
    string description;
public:
    Item (string name, string description="");
    string getName();
    string getDescription();
};

#endif /*ITEM_H_*/
