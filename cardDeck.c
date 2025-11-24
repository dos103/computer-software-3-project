/**
 * @file CardDeck.c
 * @brief Implementats CardDeck operations.
 * Author Sean Carroll
 */

#include "CardDeck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printCard(Card c);

/**
 * @brief createDeck creates a deck with numPacks of cards.
 * @param numPacks How many full sets to include.
 * @return A CardDeck with all requested packs.
 */
CardDeck createDeck(int numPacks) {
    CardDeck deck;
    deck.size = numPacks * 52;
    deck.cards = (Card*)malloc(deck.size * sizeof(Card));

    int index = 0;
    for (int p = 0; p < numPacks; p++) {
        for (int s = CLUBS; s <= DIAMONDS; s++) {
            for (int r = TWO; r <= ACE; r++) {
                deck.cards[index].suit = (Suit)s;
                deck.cards[index].rank = (Rank)r;
                index++;
            }
        }
    }
    return deck;
}

/**
 * @brief freeDeck frees the memory by clearing out the deck.
 * @param deck Pointer to the deck you want to clean up.
 */
void freeDeck(CardDeck* deck) {
    free(deck->cards);
    deck->cards = NULL;
    deck->size = 0;
}

/**
 * @brief shuffleDeck shuffles all the cards in the deck randomly.
 * @param Pointer to the deck to shuffle.
 */
void shuffleDeck(CardDeck* deck) {
    srand((unsigned int)time(NULL)); // cast to avoid warning
    for (int i = 0; i < deck->size; i++) {
        int j = rand() % deck->size;
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

/**
 * @brief bubbleSortDeck sorts the deck using bubble sort.
 * @param deck Pointer to the deck you want to sort.
 */
void bubbleSortDeck(CardDeck* deck) {
    for (int i = 0; i < deck->size - 1; i++) {
        for (int j = 0; j < deck->size - i - 1; j++) {
            if (deck->cards[j + 1].suit < deck->cards[j].suit ||
                (deck->cards[j + 1].suit == deck->cards[j].suit &&
                    deck->cards[j + 1].rank < deck->cards[j].rank)) {
                Card temp = deck->cards[j];
                deck->cards[j] = deck->cards[j + 1];
                deck->cards[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief removeTopCard takes the top card from the deck and puts it back.
 * @param deck Pointer to the CardDeck to remove the top card from.
 * @return The top Card from the deck.
 */
Card removeTopCard(CardDeck* deck) {
    if (deck->size == 0) {
        Card empty = { CLUBS, TWO };
        return empty;
    }
    Card top = deck->cards[deck->size - 1];
    deck->size--;
    return top;
}

/**
 * @brief addCard adds a new card to the bottom of the deck.
 * @param deck Pointer to the CardDeck to adding the card to.
 * @param c The Card to add.
 */
void addCard(CardDeck* deck, Card c) {
    Card* temp = (Card*)realloc(deck->cards, (deck->size + 1) * sizeof(Card));
    if (temp == NULL) {
        printf("Error: Unable to allocate memory for new card.\n");
        return;
    }
    deck->cards = temp;
    deck->cards[deck->size] = c;
    deck->size++;
}

/**
 * @brief printDeck prints every card in the deck.
 * @param deck Pointer to the card you want to print.
 */
void printDeck(CardDeck* deck) {
    for (int i = 0; i < deck->size; i++) {
        printCard(deck->cards[i]);
    }
}

/**
 * @brief printCard prints a single card in readable format.
 * @param c The card you want to print.
 */
void printCard(Card c) {
    const char* suits[] = { "Clubs", "Spades", "Hearts", "Diamonds" };
    const char* ranks[] = { "", "", "2","3","4","5","6","7","8","9","10",
                            "Jack","Queen","King","Ace" };
    printf("%s of %s\n", ranks[c.rank], suits[c.suit]);
}

