#include "CardDeck.h"
#include <stdio.h>

int main()
{
    CardDeck deck = createDeck(1);
    printf("Created deck with %d cards.\n", deck.size);

    shuffleDeck(&deck);
    printf("Deck shuffled.\n");

    bubbleSortDeck(&deck);
    printf("Deck sorted.\n");

    printDeck(&deck);

    freeDeck(&deck);
    return 0;
}

