/**
 * @file CardDeck.h
 * @brief Declaration of Card, CardDeck, and related operations.
 * Author: Sean Carroll
 */

#ifndef CARDDECK_H
#define CARDDECK_H

 /**
  * @enum Suit
  * @brief The four suits in a standard deck.
  */
typedef enum { CLUBS, SPADES, HEARTS, DIAMONDS } Suit;

/**
 * @enum Rank
 * @brief The ranks in a standard deck.
 */
typedef enum {
    TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
    JACK, QUEEN, KING, ACE
} Rank;

/**
 * @struct Card
 * @brief Represents a single playing card.
 */
typedef struct {
    Suit suit;
    Rank rank;
} Card;

/**
 * @struct CardDeck
 * @brief A dynamic array of cards and a size counter.
 */
typedef struct {
    Card* cards;  /**< Pointer to dynamic array of cards */
    int size;     /**< Current number of cards in the deck */
} CardDeck;

CardDeck createDeck(int numPacks);
void freeDeck(CardDeck* deck);
void shuffleDeck(CardDeck* deck);
void bubbleSortDeck(CardDeck* deck);
Card removeTopCard(CardDeck* deck);
void addCard(CardDeck* deck, Card c);
void printDeck(CardDeck* deck);

#endif
