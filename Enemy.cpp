#include "Enemy.h"
using namespace std;


int level = 0;//0=Fresh, 1=In-Training, 2=Rookie, 3=Champion, 4=Ultimate, 5=Mega
int attribute = 0;//0=Data, 1=Vaccine, 2=Virus
string levels[] = {"Fresh","In-Training","Rookie","Champion","Ultimate","Mega"};
string attributes[] = {"Data", "Vaccine", "Virus"};
string name = "";
int hp = 10;
Enemy::Enemy(int nlevel, int nattribute, string nname, int nhp)
{
    level = nlevel;
    attribute = nattribute;
    name = nname;
    hp = nhp;
}