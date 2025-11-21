#include <stdio.h>
#include <stdlib.h>
#include "carddeck.h"
/**
* @file test_carddeck.c
* @brief Simple test program for the CardDeck .
*
* @details This program demonstrates creating a deck of cards,
* checking its size, removing the top card, and freeing
* the deck memory.It serves as a basic usage example
* of the CardDeck API.
*/

/**
 * @brief Entry point for the test program.
 *
 * @details Performs the following steps:
 *          1. Creates a single 52-card deck using createCardDeck().
 *          2. Prints the initial size of the deck.
 *          3. Removes the top card and prints its suit and rank.
 *          4. Prints the size of the deck after removal.
 *          5. Frees all memory allocated for the deck.
 *
 * @return int Always returns 0.
 */

int main(void)
{
    CardDeck deck;// Declare a deck variable

    createCardDeck(&deck, 1);// Create a standard single pack deck (52 cards)

    // Print the number of cards in the deck
    printf("Deck created with %d cards.\n", deckSize(&deck));
  
  

    Card top; // Variable to hold removed card
    if (removeTopCard(&deck, &top)) {    // Remove the top card from the deck
        printf("Removed top card: Suit=%d Rank=%d\n", top.suit, top.rank); // Print the suit and rank of the removed card
    }

    printf("Deck now has %d cards.\n", deckSize(&deck));// Print the deck size after removing the top card

    freeCardDeck(&deck);    // Free all memory used by the deck
    return 0;  // Exit program successfully
}
