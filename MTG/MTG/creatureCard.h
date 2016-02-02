#ifndef CREATURE_CARD_H
#define CREATURE_CARD_H

#include "card.h"

class CreatureCard : public Card
{
public:
    unsigned long power;
    unsigned long toughness;
    unsigned long abilities;

    CreatureCard(char *name, char *manaCost, cardType type, cardColor color, unsigned long power, unsigned long toughness, unsigned long abilities);

    CreatureCard(CreatureCard *c);

    ~CreatureCard();

    void toString();
};


#endif
