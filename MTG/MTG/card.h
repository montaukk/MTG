#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <random>

using namespace std;

#define MAX_SIZE(x)                 sizeof(x) / sizeof(unsigned long)
#define SWAP_FRONT(x, pos)          unsigned long tmp = *x; \
                                    *x = *(x + pos); \
                                    *(x + pos) = tmp;

#define SWAP_BACK(x, pos1, pos2)    unsigned long tmp = *(x + pos1); \
                                    *(x + pos1) = *(x + pos2); \
                                    *(x + pos2) = tmp;


#define DECK_SIZE           60
#define ARMY_SIZE           100
#define LAND_SIZE           30
#define DEFAULT_HAND_SIZE   7

#define TRAMPLE             0x1
#define HASTE               0x2
#define FLYING              0x4
#define VIGILANCE           0x8
#define FIRST_STRIKE        0x10

enum cardType
{
    artifact = 1,
    aura,
    creature,
    enchantment,
    instant,
    land,
    sorcery,
};

enum cardColor
{
    black = 1,
    blue,
    green,
    red,
    white,
    colorless
};

class Card
{
public:
    char *name;
    char *manaCost;
    enum cardType type;
    enum cardColor color;
    unsigned long id;
    bool tapped;

    /* Default Constructor */
    Card();

    /* Constructor */
    Card(char *name, char *manaCost, enum cardType type, enum cardColor color);

    Card(Card *c);

    /* Default Destructor */
    ~Card();

    void toString();
};

#endif // CARD_H
