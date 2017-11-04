#ifndef ENEMY_H
#define ENEMY_H

#include <string>
using namespace std;

class Enemy
{
public:
    Enemy(int, int, string, int);
    string getName();
    string toString();
    void changeHP(int c);
    string getHP();
};

#endif // ENEMY_H
