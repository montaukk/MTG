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
        p.library[i] = p.deck[i];
    }
}

void initDeck(Player &p)
{
    int i = 0;
    for (; i < 20; i++)
    {
        //        unsigned long x = (rand() % 5) + 1;
        unsigned long x = (rand() % 3) + 3;
        p.deck[i] = x;
    }
    for (; i < DECK_SIZE; i++)
    {
        unsigned long x = (rand() % 5) + 6;
        p.deck[i] = x;
    }
}

void drawCard(Player &p)
{
    unsigned long numCardsLibrary = getNumCards((char*)p.library, MAX_SIZE(p.library), sizeof(int));
    unsigned long numCardsHand = getNumCards((char*)p.hand, MAX_SIZE(p.hand), sizeof(int));

    if (numCardsLibrary > 0 && numCardsLibrary <= DECK_SIZE)
    {
        numCardsLibrary--;
    }
    //if (numCardsHand > 0 && numCardsHand <= DEFAULT_HAND_SIZE)
    //{
    //    numCardsHand--;
    //}

    p.hand[numCardsHand] = p.library[numCardsLibrary];
    p.library[numCardsLibrary] = 0;
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
            Card *card = vault.at(p.hand[selection - 1]);

            // Attempting to play a land
            if (card->type == land && !p.playedLand)
            {
                printf("Playing %s\n", card->name);
                p.playedLand = TRUE;
                unsigned long numCardsLands = getNumCards((char*)p.lands, MAX_SIZE(p.lands), sizeof(Card *));
                unsigned long numCardsHand = getNumCards((char*)p.hand, MAX_SIZE(p.hand), sizeof(Card*));

                Card *beingPlayed = new Card(card);
                p.lands[numCardsLands] = beingPlayed;
                SWAP_BACK(p.hand, selection - 1, numCardsHand - 1);
                p.hand[numCardsHand - 1] = 0;
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

                    unsigned long numCardsArmy = getNumCards((char*)p.army, MAX_SIZE(p.army), sizeof(Card*));
                    unsigned long numCardsHand = getNumCards((char*)p.hand, MAX_SIZE(p.hand), sizeof(int));

                    printf("Can play!\n");

                    CreatureCard *beingPlayed = new CreatureCard((CreatureCard*)card);
                    p.army[numCardsArmy] = beingPlayed;
                    SWAP_BACK(p.hand, selection - 1, numCardsHand - 1);
                    p.hand[numCardsHand - 1] = 0;

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
                if (!selection || selection > getNumCards((char*)p.lands, MAX_SIZE(p.lands), sizeof(Card*)))
                {
                    printf("Invalid input\n");
                    return;
                }

                if (!p.lands[selection - 1]->tapped)
                {
                    p.lands[selection - 1]->tapped = true;
                    switch (p.lands[selection - 1]->color)
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
                    printf("%s already tapped!\n", p.lands[i]->name);
                }
            }
        }
    }

}

void untapStep(Player &p)
{
    unsigned long numCardsArmy = getNumCards((char*)p.army, MAX_SIZE(p.army), sizeof(Card*));
    unsigned long numCardsLands = getNumCards((char*)p.lands, MAX_SIZE(p.lands), sizeof(Card*));
    for (int i = 0; i < numCardsArmy; i++)
    {
        p.army[i]->tapped = false;
    }
    for (int i = 0; i < numCardsLands; i++)
    {
        p.lands[i]->tapped = false;
    }
}
