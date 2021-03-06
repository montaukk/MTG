#ifndef CARDS_H
#define CARDS_H

#include <Windows.h>
#include "creatureCard.h"
#include "player.h"
#include "display.h"
#include "cardContainer.h"

struct ManaCost
{
    unsigned long black;
    unsigned long blue;
    unsigned long green;
    unsigned long red;
    unsigned long white;
    unsigned long colorless;
    unsigned long converted;
};

unsigned long getNumCards(char *, unsigned int, unsigned int);
void initLibrary(class Player &p);
void initDeck(class Player &p);
void drawCard(class Player &p);
void drawHand(class Player &p);
void shuffle(unsigned long *, unsigned int);
void playCard(class Player &p, std::map<unsigned long, Card *> &vault);
void tapMana(class Player &p);
void untapStep(class Player &p);

#endif // CARDS_H
