#include "cards.h"

unsigned long getNumCards(char *arr, unsigned int arrSize, unsigned int dataSize)
{
    int i = 0;

    if (arr == nullptr)
    {
        printf("Error, arr was null!\n");
        return 0;
    }

    for (; i < arrSize; i++)
    {
        if (!*(arr + (i * dataSize)))
        {
            break;
        }
    }
    return i;
}

void initLibrary(Player &p)
{
    for (int i = 0; i < p.deck._size(); i++)
    {
        p.library.add(p.deck.at(i));
    }
}

void initDeck(Player &p)
{
    int i = 0;
    for (; i < 20; i++)
    {
        //        unsigned long x = (rand() % 5) + 1;
        unsigned long x = (rand() % 3) + 3;
        p.deck.add(x);
    }
    for (; i < DECK_SIZE; i++)
    {
        unsigned long x = (rand() % 5) + 6;
        p.deck.add(x);
    }
}

void drawCard(Player &p)
{
    unsigned long numCardsLibrary = p.library._size();
    unsigned long numCardsHand = p.hand._size();

    if (numCardsLibrary > 0 && numCardsLibrary <= DECK_SIZE)
    {
        numCardsLibrary--;
    }
    /* TODO: reinable hand size when done testing
    if (numCardsHand > 0 && numCardsHand <= DEFAULT_HAND_SIZE)
    {
        numCardsHand--;
    }
    */

    p.hand.drawFrom(p.library);
}

void drawHand(Player &p)
{
    for (int i = 0; i < DEFAULT_HAND_SIZE; i++)
        drawCard(p);
}

void shuffle(unsigned long *library, unsigned int size)
{
    for (int i = 0; i < 400; i++)
    {
        int pos = rand() % size;
        SWAP_FRONT(library, pos)
    }
}

void calculateManaCost(char *cost, unsigned long manaCostLen, ManaCost *requiredMana)
{
    int i = 0;
    if (atoi(cost))
    {
        requiredMana->colorless += atoi(cost);
        requiredMana->converted += atoi(cost);
        i++;
    }
    for (; i < manaCostLen; i++)
    {
        switch (*(cost + i))
        {
        case 'B':
            requiredMana->black++;
            break;
        case 'U':
            requiredMana->blue++;
            break;
        case 'G':
            requiredMana->green++;
            break;
        case 'R':
            requiredMana->red++;
            break;
        case 'W':
            requiredMana->white++;
            break;
        }
        requiredMana->converted++;
    }
}

void playCard(Player &p, map<unsigned long, Card *> &vault)
{
    char line[256] = { 0 };
    char input = ' ';

    printHand(p, vault);

    if (fgets(line, sizeof(line), stdin))
    {
        if (1 == sscanf_s(line, "%c", &input))
        {
            int selection = atoi(&input);
            if (!selection)
            {
                printf("Invalid input\n");
                return;
            }
            Card *card = vault.at(p.hand.at(selection - 1));

            // Attempting to play a land
            if (card->type == land && !p.playedLand)
            {
                printf("Playing %s\n", card->name);
                p.playedLand = TRUE;
                unsigned long numCardsLands = p.lands._size();
                unsigned long numCardsHand = p.hand._size();

                Card *beingPlayed = new Card(card);
                p.lands.add(beingPlayed);
                p.hand.remove(p.hand._begin() + (selection - 1));
                //SWAP_BACK(p.hand, selection - 1, numCardsHand - 1);
                //p.hand[numCardsHand - 1] = 0;
            }
            else if (card->type == land) {
                // Already played a land this turn, can't play 2
                printf("You already played a land this turn!\n");
            }
            else {
                // Attempting to play non land card
                printf("Requires %s mana\n", card->manaCost ? card->manaCost : "no");

                ManaCost cost = { 0 };
                calculateManaCost(card->manaCost, strlen(card->manaCost), &cost);

                // TODO: Figure out how to recognize colorless mana...
                if (p.blackMana >= cost.black &&
                    p.blueMana >= cost.blue &&
                    p.greenMana >= cost.green &&
                    p.redMana >= cost.red &&
                    p.whiteMana >= cost.white &&
                    p.colorlessMana >= cost.colorless)
                {
                    p.blackMana -= cost.black;
                    p.blueMana -= cost.blue;
                    p.greenMana -= cost.green;
                    p.redMana -= cost.red;
                    p.whiteMana -= cost.white;
                    p.colorlessMana -= cost.colorless;

                    unsigned long numCardsArmy = p.army._size();
                    unsigned long numCardsHand = p.hand._size();

                    printf("Can play!\n");

                    CreatureCard *beingPlayed = new CreatureCard((CreatureCard*)card);
                    p.army.add(beingPlayed);
                    p.hand.remove(p.hand._begin() + (selection - 1));
                }
                else {
                    printf("Which cards will you tap for mana?\n");
                    printCards(p, land);


                    printf("Insufficient Mana!!\n");
                }
            }
        }
    }
}

void tapMana(Player &p)
{
    char line[256] = { 0 };
    char input = ' ';

    printCards(p, land, true);

    if (fgets(line, sizeof(line), stdin))
    {
        int lineLen = strlen(line) - 1;
        for (int i = 0; i < lineLen; i++)
        {
            if (1 == sscanf_s(line + i, "%c", &input))
            {
                int selection = atoi(&input);
                if (!selection || selection > p.lands._size())
                {
                    printf("Invalid input\n");
                    return;
                }

                if (!p.lands.at(selection - 1)->tapped)
                {
                    p.lands.at(selection - 1)->tapped = true;
                    switch (p.lands.at(selection - 1)->color)
                    {
                    case black:
                        p.blackMana++;
                        break;
                    case blue:
                        p.blueMana++;
                        break;
                    case green:
                        p.greenMana++;
                        break;
                    case red:
                        p.redMana++;
                        break;
                    case white:
                        p.whiteMana++;
                        break;
                    case colorless:
                        p.colorlessMana++;
                        break;
                    }
                    p.convertedMana++;
                }
                else {
                    printf("%s already tapped!\n", p.lands.at(i)->name);
                }
            }
        }
    }

}

void untapStep(Player &p)
{
    unsigned long numCardsArmy = p.army._size();
    unsigned long numCardsLands = p.army._size();
    for (int i = 0; i < numCardsArmy; i++)
    {
        p.army.at(i)->tapped = false;
    }
    for (int i = 0; i < numCardsLands; i++)
    {
        p.lands.at(i)->tapped = false;
    }
}
