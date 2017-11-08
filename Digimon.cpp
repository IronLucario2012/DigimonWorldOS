#include "Digimon.h"
using namespace std;

Digimon::Digimon()
{
    name = "Placeholder";
    hp = 10;
    xp = 0;
}

Digimon::Digimon(int nlevel, int nattribute, string nname, int nhp, string nimg)
{
    level = nlevel;
    attribute = nattribute;
    name = nname;
    hp = nhp;
    imgPath = nimg;
    xp = 0;
}
string Digimon::getName()
{
    return name;
}
int Digimon::getAttribute()
{
    return attribute;
}
int Digimon::getLevel()
{
    return level;
}
const string Digimon::toString()
{
    string out = "Name: " + name + ", Level: " + levels[level] + ", Attribute: " + attributes[attribute] + ", HP: " + getHPString();
    return out;
}
void Digimon::changeHP(int c)
{
    hp += c;
}
string Digimon::getHPString()
{
    string out = to_string(hp);
    return out;
}
int Digimon::getHP()
{
    return hp;
}
QPixmap Digimon::getPix()
{
    QPixmap enemyPix = QString::fromStdString(imgPath);
    QPixmap finalEnemyPix = enemyPix.scaled(QSize(200,200), Qt::KeepAspectRatio);
    return finalEnemyPix;
}
int Digimon::rockPaperScissors(int p1, int p2)
{
    //Each number beats the number one above it, looping around so 2 beats 0
    //Returns 0 if a draw, otherwise returns which number won
    //Can be used for both type comparisons and attack comparisons
    int out = 0;
    if((p1+1)%3==p2)
        out = 1;
    else if((p2+1)%3==p1)
        out = 2;

    return out;
}

string Digimon::fight(Digimon* enemy, int atkUsed)
{
    string out = "You attacked " + enemy->getName() + " with a " + attacks[atkUsed] + " attack.\n";
    int enemyAtk = rand()%3;

    out += enemy->getName() + " attacked you with a " + attacks[enemyAtk] + " attack.\n";

    int result = rockPaperScissors(atkUsed,enemyAtk);
    int attAdv = rockPaperScissors(attribute,enemy->getAttribute());
    int levelAdv = enemy->getLevel()-level;

    int playerDamage = -3, enemyDamage = -3;

    switch(attAdv)
    {
    case 1: playerDamage -= 1;enemyDamage += 1; break;
    case 2: playerDamage += 1;enemyDamage -= 1; break;
    default:break;
    }
    playerDamage -= levelAdv*2;
    enemyDamage += levelAdv*2;
    if(playerDamage>0)
        playerDamage = 0;
    if(enemyDamage>0)
        enemyDamage = 0;

    switch(result)
    {
    case 0: out += "You both take 1 damage!";
            changeHP(-1);
            enemy->changeHP(-1);
        break;
    case 1: out += enemy->getName() + " takes " + to_string(playerDamage) + " damage!";
            enemy->changeHP(playerDamage);
        break;
    case 2: out += "You take " + to_string(enemyDamage) + " damage!";
            changeHP(enemyDamage);
        break;
    }

    out += "\nYour hp is " + getHPString() + ".\n" + enemy->getName() + "'s hp is " + enemy->getHPString() + ".";

    if(hp < 1)
    {
        out += "\nYou died";
        //TODO: Game over.
    }
    else if(enemy->getHP() < 1)
    {
        out += "\nYou won";
    }
    return out;
}

void Digimon::addXP()
{
    xp++;
    hp += 4;
    if(xp>=3)
    {
        level = 3;
        name = "Bao Hackmon";
        xp = 0;
        hp = 30;
    }
}



