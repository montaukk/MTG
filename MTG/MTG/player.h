#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include "cards.h"

using namespace std;

class Player
{
public:
    char *name;

    unsigned long health;

    unsigned long blackMana;
    unsigned long blueMana;
    unsigned long greenMana;
    unsigned long redMana;
    unsigned long whiteMana;
    unsigned long colorlessMana;

    bool playedLand;

    std::vector<unsigned long> deck;
    std::vector<unsigned long> library; 
    std::vector<unsigned long> hand;
    std::vector<unsigned long> graveyard;
    std::vector<Card *> army;
    std::vector<Card *> lands;
    //    unsigned long tapped[ARMY_SIZE];

    Player(char *name);

    ~Player();

    void toString();

    void print(unsigned long *arr, unsigned long size, map<int, Card> &vault);
};

#endif
