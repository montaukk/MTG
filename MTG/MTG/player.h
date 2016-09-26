#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include "cards.h"
#include "cardContainer.h"

using namespace std;

class Player
{
public:
    char *name;

    long health;

    unsigned long blackMana;
    unsigned long blueMana;
    unsigned long greenMana;
    unsigned long redMana;
    unsigned long whiteMana;
    unsigned long colorlessMana;
    unsigned long convertedMana;

    bool playedLand;

    cardContainer<unsigned long> deck;
    cardContainer<unsigned long> library;
    cardContainer<unsigned long> hand;
    cardContainer<unsigned long> graveyard;
    cardContainer<Card *> army;
    cardContainer<Card *> lands;

    Player(char *name);

    ~Player();

    void toString();

    void print(unsigned long *arr, unsigned long size, map<int, Card> &vault);
};

#endif
