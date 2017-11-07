#ifndef DIGIMON_H
#define DIGIMON_H

#include <string>
#include <QtGui>

using namespace std;

class Digimon
{
public:
    Digimon();
    Digimon(int, int, string, int, string);
    string getName();
    const string toString();
    void changeHP(int c);
    string getHP();
    int rockPaperScissors(int p1, int p2);
    string fight(int atkUsed);
    QPixmap getPix();
};

#endif // DIGIMON_H
