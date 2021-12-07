#include "player.h"

player::player()
{
    //初始化各种属性
       Hp=100;
       Mp=50;
       extraPower=0;
       shield=0;
       exp=0;
       level=1;
       isAct=1;
}

int player::getHp()
{
     return Hp;
}

int player::getMp()
{
    return Mp;
}

int player::getExtraPower()
{
    return extraPower;
}

int player::getShield()
{
    return shield;
}

int player::getExp()
{
    return exp;
}

int player::getLevel()
{
    return level;
}

int player::getIsAct()
{
    return isAct;
}

void player::setHp(int a)
{

    Hp+=a;
    if(Hp<0) Hp=0;

}

void player::setMp(int a)
{
    Mp+=a;
    if(Mp<0) Mp=0;
}

void player::setExtraPower(int a)
{

}

void player::setShield(int a)
{

}

void player::setExp(int a)
{

}

void player::setLevel(int a)
{

}

void player::setIsAct(int a)
{

}


