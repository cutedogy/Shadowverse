#ifndef PLAYER_H
#define PLAYER_H


class player
{
public:
    player();
    int getHp();
    int getMp();
    int getExtraPower();
    int getShield();
    int getExp();
    int getLevel();
    int getIsAct();

    void setHp(int a);
    void setMp(int a);
    void setExtraPower(int a);
    void setShield(int a);
    void setExp(int a);
    void setLevel(int a);
    void setIsAct(int a);

private:
    int Hp;//血量
    int Mp;//能量
    int extraPower;//额外增伤
    int shield;//护盾
    int exp;//经验
    int level;//等级
    int isAct;//是否可以行动
};

#endif // PLAYER_H
