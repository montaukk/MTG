#include <Windows.h>
#include <stdio.h>
#include "cards.h"
#include "player.h"
#include "display.h"
#include <random>
#include <time.h>
#include <map>

map<unsigned long, Card *> vault;

void initVault()
{
    vault.insert(pair<unsigned long, Card *>(1, new Card("Swamp", nullptr, land, black)));
    vault.insert(pair<unsigned long, Card *>(2, new Card("Island", nullptr, land, blue)));
    vault.insert(pair<unsigned long, Card *>(3, new Card("Forest", nullptr, land, green)));
    vault.insert(pair<unsigned long, Card *>(4, new Card("Mountain", nullptr, land, red)));
    vault.insert(pair<unsigned long, Card *>(5, new Card("Plains", nullptr, land, white)));
    vault.insert(pair<unsigned long, Card *>(6, new CreatureCard("Suntailed Hawk", "W", creature, white, 1, 1, FLYING)));
    vault.insert(pair<unsigned long, Card *>(7, new CreatureCard("Tundra Wolves", "W", creature, white, 1, 1, FIRST_STRIKE)));
    vault.insert(pair<unsigned long, Card *>(8, new CreatureCard("Defiant Elf", "G", creature, green, 1, 1, TRAMPLE)));
    vault.insert(pair<unsigned long, Card *>(9, new CreatureCard("Raging Goblin", "R", creature, red, 1, 1, HASTE)));
    vault.insert(pair<unsigned long, Card *>(10, new CreatureCard("Courier Hawk", "1W", creature, white, 1, 2, FLYING | VIGILANCE)));
}


void takeTurn(Player &player, Player &opponent)
{
    char line[256] = { 0 };
    char input = ' ';

    clearBoard();
    printf("%s's Turn!\n", player.name);
    player.playedLand = FALSE;
    untapStep(player);
    drawCard(player);

    while (input != 'd')
    {
        printBoard(player, opponent);

        if (fgets(line, sizeof(line), stdin))
        {
            if (1 == sscanf_s(line, "%c", &input))
            {
                switch (input)
                {
                case 'p':
                    playCard(player, vault);
                    break;
                case 'a':
                    printCards(player, creature, true);
                    break;
                case 'm':
                    tapMana(player);
                    break;
                case 'd':
                    printf("Ending turn\n");
                    break;
                default:
                    printf("invalid option\n");
                    break;
                }
            }
        }
    }
}

void startMatch(Player &p1, Player &p2)
{
    printf("Starting match: %s vs %s\n", p1.name, p2.name);

    shuffle(p1.library, getNumCards((char*)p1.library, MAX_SIZE(p1.library), sizeof(Card*)));
    shuffle(p2.library, getNumCards((char*)p2.library, MAX_SIZE(p2.library), sizeof(Card*)));

    drawHand(p1);
    drawHand(p2);

    while (true)
    {
        takeTurn(p1, p2);
        takeTurn(p2, p1);
        if (p1.health <= 0 || p2.health <= 0)
        {
            printf("%s WINS\n", p1.health ? p1.name : p2.name);
            break;
        }
    }
}

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));
    Player me("Me");
    Player you("You");

    me.toString();
    you.toString();

    initVault();

    initDeck(me);
    initLibrary(me);
    initDeck(you);
    initLibrary(you);

    printf("%s's deck: %d\n", me.name, getNumCards((char*)me.deck, MAX_SIZE(me.deck), sizeof(int)));
    printf("%s's deck: %d\n", you.name, getNumCards((char*)you.deck, MAX_SIZE(you.deck), sizeof(int)));

    startMatch(me, you);

    system("PAUSE");

    return 0;
}
