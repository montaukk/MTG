#ifndef DISPLAY_H
#define DISPLAY_H

#include "player.h"

// Properties 230 x 80
#define BOARD_WIDTH     230
#define BOARD_HEIGHT    80

void printMenu();
void clearBoard();
void printBoard(class Player &p1, class Player &p2);
void printHand(class Player &p, std::map<unsigned long, Card *> &vault);
void printArmy(class Player &p);
void printCards(class Player &p, cardType type, bool numbered = false);


#endif // DISPLAY_H
