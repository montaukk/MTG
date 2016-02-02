#ifndef PLAYER_H
#define PLAYER_H

#include <map>
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

    unsigned long deck[DECK_SIZE];
    unsigned long library[DECK_SIZE];
    unsigned long hand[DEFAULT_HAND_SIZE + 3];
    unsigned long graveyard[DECK_SIZE];
    Card *army[ARMY_SIZE];
    Card *lands[LAND_SIZE];
    //    unsigned long tapped[ARMY_SIZE];

    Player(char *name);

    ~Player();

    void toString();

    void print(unsigned long *arr, unsigned long size, map<int, Card> &vault);
};

#endif
