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
    for (int i = 0; i < DECK_SIZE; i++)
    {
        unsigned long x = p.deck.at(i);
        p.library.push_back(x);
    }
}

void initDeck(Player &p)
{
    int i = 0;
    for (; i < 20; i++)
    {
        //        unsigned long x = (rand() % 5) + 1;
        unsigned long x = (rand() % 3) + 3;
        p.deck.push_back(x);
    }
    for (; i < DECK_SIZE; i++)
    {
        unsigned long x = (rand() % 5) + 6;
        p.deck.push_back(x);
    }
}

void drawCard(Player &p)
{
    unsigned long numCardsLibrary = p.library.size();
    unsigned long numCardsHand = p.hand.size();

    if (numCardsLibrary > 0 && numCardsLibrary <= DECK_SIZE)
    {
        numCardsLibrary--;
    }
    //if (numCardsHand > 0 && numCardsHand <= DEFAULT_HAND_SIZE)
    //{
    //    numCardsHand--;
    //}

    p.hand.push_back(p.library.back());
    p.library.pop_back();
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
                unsigned long numCardsLands = p.lands.size();
                unsigned long numCardsHand = p.hand.size();

                Card *beingPlayed = new Card(card);
                p.lands.push_back(beingPlayed);
                p.hand.erase(p.hand.begin() + (selection - 1));
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
                unsigned long blackManaRequired = 0;
                unsigned long blueManaRequired = 0;
                unsigned long greenManaRequired = 0;
                unsigned long redManaRequired = 0;
                unsigned long whiteManaRequired = 0;
                unsigned long colorlessManaRequired = 0;

                unsigned long manaCostLen = strlen(card->manaCost);

                for (int i = 0; i < manaCostLen; i++)
                {
                    char ch = *(card->manaCost + i);
                    switch (ch)
                    {
                    case 'B':
                        blackManaRequired++;
                        break;
                    case 'U':
                        blueManaRequired++;
                        break;
                    case 'G':
                        greenManaRequired++;
                        break;
                    case 'R':
                        redManaRequired++;
                        break;
                    case 'W':
                        whiteManaRequired++;
                        break;
                    default:
                        char buff[2] = { 0 };
                        buff[0] = ch;
                        if (atoi(buff))
                            colorlessManaRequired = atoi(buff);
                    }
                }
                if (p.blackMana >= blackManaRequired &&
                    p.blueMana >= blueManaRequired &&
                    p.greenMana >= greenManaRequired &&
                    p.redMana >= redManaRequired &&
                    p.whiteMana >= whiteManaRequired &&
                    p.colorlessMana >= colorlessManaRequired)
                {
                    p.blackMana -= blackManaRequired;
                    p.blueMana -= blueManaRequired;
                    p.greenMana -= greenManaRequired;
                    p.redMana -= redManaRequired;
                    p.whiteMana -= whiteManaRequired;
                    p.colorlessMana -= colorlessManaRequired;

                    unsigned long numCardsArmy = p.army.size();
                    unsigned long numCardsHand = p.hand.size();

                    printf("Can play!\n");

                    CreatureCard *beingPlayed = new CreatureCard((CreatureCard*)card);
                    p.army.push_back(beingPlayed);
                    p.hand.erase(p.hand.begin() + (selection - 1));
                    //SWAP_BACK(p.hand, selection - 1, numCardsHand - 1);
                    //p.hand[numCardsHand - 1] = 0;

                }
                else {
                    printf("Which cards will you tap for mana?\n");
                    printCards(p, land);


                    printf("CANNOT PLAY THIS CARD!!\n");
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
                if (!selection || selection > p.lands.size())
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
    unsigned long numCardsArmy = p.army.size();
    unsigned long numCardsLands = p.army.size();
    for (int i = 0; i < numCardsArmy; i++)
    {
        p.army.at(i)->tapped = false;
    }
    for (int i = 0; i < numCardsLands; i++)
    {
        p.lands.at(i)->tapped = false;
    }
}
