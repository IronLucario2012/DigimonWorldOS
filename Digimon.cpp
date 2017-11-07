#include "Digimon.h"
using namespace std;


int level = 0;//0=Fresh, 1=In-Training, 2=Rookie, 3=Champion, 4=Ultimate, 5=Mega
int attribute = 0;//0=Data, 1=Vaccine, 2=Virus
string levels[] = {"Fresh","In-Training","Rookie","Champion","Ultimate","Mega"};
string attributes[] = {"Data", "Vaccine", "Virus"};
string attacks[] = {"heavy","light","ranged"};
string name = "";
int hp = 10;
string imgPath = "";

Digimon::Digimon()
{
    name = "Placeholder";
    hp = 10;
}

Digimon::Digimon(int nlevel, int nattribute, string nname, int nhp, string nimg)
{
    level = nlevel;
    attribute = nattribute;
    name = nname;
    hp = nhp;
    imgPath = nimg;
}
string Digimon::getName()
{
    return name;
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

string Digimon::fight(Digimon enemy, int atkUsed)
{
    string out = "You attacked " + this->getName() + " with a " + attacks[atkUsed] + " attack.\n";
    int enemyAtk = 0; //TODO: Make a random number

    out += this->getName() + " attacked you with a " + attacks[enemyAtk] + " attack.\n";

    int result = rockPaperScissors(atkUsed,enemyAtk);

    switch(result)
    {
    case 0: out += "You both take 3 damage!";
            changeHP(-3);
            enemy.changeHP(-3);
        break;
    case 1: out += enemy.getName() + " takes 3 damage!";
            enemy.changeHP(-3);
        break;
    case 2: out += "You take 3 damage!";
            changeHP(-3);
        break;
    }

    out += "Your hp is " + getHPString() + ".\n" + enemy.getName() + "'s hp is " + enemy.getHPString() + ".\n";

    if(hp < 1)
    {
        out += "\nYou died";
    }
    else if(enemy.getHP() < 1)
    {
        out += "\nYou won";
    }
    return out;
}





