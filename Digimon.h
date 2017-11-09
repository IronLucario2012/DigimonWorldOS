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
    string getHPString();
    int getHP();
    int rockPaperScissors(int p1, int p2);
    string fight(Digimon* enemy,int atkUsed);
    QPixmap getPix();
    string addXP();
    int getAttribute();
    int getLevel();
    int getXP();
    int levelCompare(int p2);

private:
    int level;//0=Fresh, 1=In-Training, 2=Rookie, 3=Champion, 4=Ultimate, 5=Mega
    int attribute;//0=Data, 1=Vaccine, 2=Virus
    string levels[6] = {"Fresh","In-Training","Rookie","Champion","Ultimate","Mega"};
    string attributes[3] = {"Data", "Vaccine", "Virus"};
    string attacks[3] = {"heavy","light","ranged"};
    string name;
    int hp;
    int xp;
    string imgPath;
};

#endif // DIGIMON_H
