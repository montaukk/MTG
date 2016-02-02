#include "card.h"

/* Default Constructor */
Card::Card()
    : name(nullptr), manaCost(nullptr)
{

}

Card::Card(char *name, char *manaCost, enum cardType type, enum cardColor color)
    : name(name), manaCost(manaCost), type(type), color(color), tapped(false)
{
    id = rand();
}

Card::Card(Card *c)
    : name(c->name), manaCost(c->manaCost), type(c->type), color(c->color), tapped(false)
{
    id = rand();
}

/* Default Destructor */
Card::~Card()
{

}

void Card::toString()
{
    printf("Name:		%s\n", name);
    printf("Mana Cost:	%s\n", manaCost);
    switch (type)
    {
    case creature:
        printf("Type:		Creature\n");
        break;
    case enchantment:
        printf("Type:		Enchantment\n");
        break;
    case land:
        printf("Type:		Land\n");
        break;
    case instant:
        printf("Type:		Instant\n");
        break;
    case sorcery:
        printf("Type:		Sorcery\n");
        break;
    case aura:
        printf("Type:		Aura\n");
        break;
    }

    switch (color)
    {
    case white:
        printf("Color:		White\n");
        break;
    case green:
        printf("Color:		Green\n");
        break;
    case black:
        printf("Color:		Black\n");
        break;
    case red:
        printf("Color:		Red\n");
        break;
    case blue:
        printf("Color:		Blue\n");
        break;
    case colorless:
        printf("Color:		Colorless\n");
        break;

    }

}