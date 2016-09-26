#include "player.h"

Player::Player(char *name)
    : name(name), blackMana(0), blueMana(0), greenMana(0), redMana(0), whiteMana(0), colorlessMana(0), playedLand(0), 
    deck(DECK_SIZE), library(DECK_SIZE), hand(DEFAULT_HAND_SIZE), graveyard(DECK_SIZE), army(ARMY_SIZE), lands(LAND_SIZE)
{
    health = 20;
}

Player::~Player()
{
}

void Player::toString()
{
    printf("Name:           %s\n", name);
    printf("Health:         %d\n", health);
}

void Player::print(unsigned long *arr, unsigned long size, map<int, Card> &vault)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", i);
        unsigned long id = *(arr + i);
        Card c = vault.at(id);
        c.toString();
    }
}
