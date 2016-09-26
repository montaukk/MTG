#include "display.h"

char *cardTypes[] = { "NULL", "artifact", "aura", "creature", "enchantment", "instant", "land", "sorcery" };
char *cardColors[] = { "NULL", "black", "blue", "green", "red", "white", "colorless" };

void printMenu()
{
    char *menu[] = { "----------------------------------------" ,
        "Choose an option:" ,
        "   p - play a card" ,
        "   a - activate a cards ability" ,
        "   m - tap lands for mana" ,
        "   d - done, end turn" ,
        "----------------------------------------" ,
        nullptr };
    unsigned long menuWidth = strlen(menu[0]);

    for (int i = 0; menu[i] != nullptr; i++)
    {
        if (menu[i][0] == '-')
        {
            printf(" %s \n", menu[i]);
        }
        else
        {
            printf("|%s%*s|\n", menu[i], (menuWidth - strlen(menu[i])), " ");
        }
    }
}

void clearBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
        printf("\n");
}

void printBoard(Player &player, Player &opponent)
{
    printCards(opponent, land);

    printCards(opponent, creature);

    printMenu();

    // Army
    printCards(player, creature);

    // Lands
    printCards(player, land);

}

void printHand(Player &p, map<unsigned long, Card *> &vault)
{
    unsigned long numCardsHand = p.hand._size();
    for (int i = 0; i < numCardsHand; i++)
    {
        Card *c = vault.at(p.hand.at(i));
        printf("(%d)%s %s\n", i + 1, c->name, c->manaCost ? c->manaCost : "");
    }

    printf("\n");
}

void printArmy(Player &p)
{
    char *cardTemplate[] = { " ------------  ", "|%s %s%*s| " , "|%*s| " , "|%*s| ", "|%*s| " , "|%*s| " , " ------------  ", "               " };
    unsigned long cardWidth = strlen("------------");
    unsigned long numCardsArmy = p.army._size();

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < numCardsArmy; j++)
        {
            Card *c = p.army.at(j);
            char buff[100] = { 0 };
            switch (i)
            {
            case 0:
            case 6:
                sprintf_s(buff, sizeof(buff), cardTemplate[i]);
                break;
            case 1:
                sprintf_s(buff, sizeof(buff), cardTemplate[i], (c->tapped ? "T" : " "), c->name, cardWidth - (2 + strlen(c->name)), " ");
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                sprintf_s(buff, sizeof(buff), cardTemplate[i], cardWidth, " ");
                break;
            default:
                sprintf_s(buff, sizeof(buff), cardTemplate[7]);
            }
            printf("%s", buff);
        }
        printf("\n");
    }
}

void printCards(Player &p, cardType type, bool numbered)
{
    char *cardTemplate[] = { " ------------  ", "|%s %*s| " , "|%*s| " , "|%*s| ", "|%*s| " , "|%*s| " , " ------------  ", "               " };
    char *numberedCard = "|%s(%d)%*s| ";
    char *powerToughness = "|%*s%d/%d| ";

    unsigned long cardWidth = strlen("------------");
    unsigned long numCards = 0;
    if (type == land)
        numCards = p.lands._size();
    else if (type == creature)
        numCards = p.army._size();

    for (int i = 0; i < 7 && numCards; i++)
    {
        for (int j = 0; j < numCards; j++)
        {
            Card *c = NULL;
            if (type == land)
                c = p.lands.at(j);
            else if (type == creature)
                c = p.army.at(j);
            char buff[100] = { 0 };
            switch (i)
            {
            case 0:
            case 6:
                sprintf_s(buff, sizeof(buff), cardTemplate[i]);
                break;
            case 1:
                if (numbered)
                    sprintf_s(buff, sizeof(buff), numberedCard, (c->tapped ? "T" : " "), j + 1, cardWidth - (3 + (j > 8 ? 2 : 1)), c->name);
                else
                    sprintf_s(buff, sizeof(buff), cardTemplate[i], (c->tapped ? "T" : " "), cardWidth - 2, c->name);
                break;
            case 3:
                sprintf_s(buff, sizeof(buff), cardTemplate[i], cardWidth, cardTypes[c->type]);
                break;
            case 2:
            case 4:
                sprintf_s(buff, sizeof(buff), cardTemplate[i], cardWidth, " ");
                break;
            case 5:
                if (type == creature)
                {
                    sprintf_s(buff, sizeof(buff), powerToughness, cardWidth - ((((CreatureCard*)c)->power > 9 ? 2 : 1) + (((CreatureCard*)c)->toughness > 9 ? 2 : 1) + 1), " ", ((CreatureCard*)c)->power, ((CreatureCard*)c)->toughness);
                }
                else
                {
                    sprintf_s(buff, sizeof(buff), cardTemplate[i], cardWidth, " ");
                }
                break;
            default:
                sprintf_s(buff, sizeof(buff), cardTemplate[7]);
            }
            int x = strlen(buff);
            if (strlen(buff) > cardWidth + 3)
                memcpy(buff + cardWidth - 1, "..| ", strlen("..| ") + 1);
            printf("%s", buff);
        }
        printf("\n");
    }
}

//void printStackedLands(Player &player)
//{
//    unsigned long numCardsLands = getNumCards((char*)player.lands, MAX_SIZE(player.lands), sizeof(Card*));
//    char *cardTemplate[] = { " ------------  ", "|%s %s%*s| " , "|%*s| " , "|%*s| ", "|%*s| " , "|%*s| " , " ------------  ", "               " };
//    unsigned long cardWidth = strlen("------------");
//
//    unsigned long max = 0;
//    unsigned long numCardsPerPile[10] = { 0 };
//    unsigned long printProgress[10] = { 0 };
//    unsigned long numPiles = 0;
//    for (int i = 0; i < numCardsLands; i++)
//    {
//        numCardsPerPile[player.lands[i]->color]++;
//        if (numCardsPerPile[player.lands[i]->color] > max)
//            max = numCardsPerPile[player.lands[i]->color];
//    }
//
//    for (int i = 0; i < 10; i++)
//    {
//        if (numCardsPerPile[i])
//            numPiles++;
//    }
//
//    for (int i = 0; i < (7 + ((max - 1) * 2)); i++)
//    {
//        for (int j = 0, k = 0; k < numPiles; j++)
//        {
//            if (!numCardsPerPile[j])
//            {
//                continue;
//            }
//            if (printProgress[j] >= 2 && numCardsPerPile[j] >(i / 2))
//            {
//                printProgress[j] = 0;
//            }
//
//            //            Card *c = player.lands[(numPiles * (i / 2)) + k];
//            Card *c = vault.at(j);
//            char buff[100] = { 0 };
//
//            switch (printProgress[j])
//            {
//            case 0:
//            case 6:
//                sprintf_s(buff, sizeof(buff), cardTemplate[printProgress[j]++]);
//                break;
//            case 1:
//                sprintf_s(buff, sizeof(buff), cardTemplate[printProgress[j]++], (c->tapped ? "T" : " "), c->name, cardWidth - (2 + strlen(c->name)), " ");
//                break;
//            case 2:
//            case 3:
//            case 4:
//            case 5:
//                sprintf_s(buff, sizeof(buff), cardTemplate[printProgress[j]++], cardWidth, " ");
//                break;
//            default:
//                sprintf_s(buff, sizeof(buff), cardTemplate[7]);
//            }
//            printf("%s", buff);
//            k++;
//        }
//        printf("\n");
//    }
//}
//
