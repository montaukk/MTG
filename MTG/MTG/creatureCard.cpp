#include "creatureCard.h"

CreatureCard::CreatureCard(char *name, char *manaCost, cardType type, cardColor color, unsigned long power, unsigned long toughness, unsigned long abilities)
    : Card(name, manaCost, type, color), power(power), toughness(toughness), abilities(abilities)
{

}

CreatureCard::CreatureCard(CreatureCard *c)
    : Card(c->name, c->manaCost, c->type, c->color), power(c->power), toughness(c->toughness), abilities(c->abilities)
{

}

CreatureCard::~CreatureCard()
{

}

void CreatureCard::toString()
{
    Card::toString();
    printf("Power/Toughness %d\\%d\n", power, toughness);
    printf("Abilities:      ");
    if (abilities & TRAMPLE)
        printf("Trample, ");
    if (abilities & HASTE)
        printf("Haste, ");
    if (abilities & FLYING)
        printf("Flying, ");
    if (abilities & VIGILANCE)
        printf("Vigilance, ");
    printf("\n");
}
