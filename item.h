#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
    string name;
public:
    Item (string name);
    string getName();
};

#endif /*ITEM_H_*/
