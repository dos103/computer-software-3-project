#include <stdio.h>
#include <stdlib.h>
#include "carddeck.h"

/**
 * @brief Initialize an empty deck.
 * @details Sets the deck's head pointer to NULL and size to 0.
 *          This function must be called before adding any cards.
 * @param[in,out] deck Pointer to the CardDeck to initialize.
 * 
 */
void initCardDeck(CardDeck* deck)
{
    deck->head = NULL; // No cards yet
    deck->size = 0;    // Size starts at 0
}

/**
 * @brief Create a new node for a card.
 *  @details Allocates memory for a CardNode, sets the card value,
 *          and initializes the next pointer to NULL. Exits the
 *          program if memory allocation fails.
 * @param c Card to store.
 * @return CardNode* n Pointer to allocated node.
 */
static CardNode* createNode(Card c)
{
    CardNode* node = malloc(sizeof(CardNode));
    if (!node) {
        printf(stderr, "Memory allocation failed in createNode() "); 
        exit(EXIT_FAILURE); // Fatal error
    }
    node->card = c;     // Store card in node
    node->next = NULL;  // Initially no next node
    return node;
}

/**
 * * @brief Add a card to the top of the deck.
 * 
 * @details Inserts the new card at the head of the linked list,
 *          making it the new top card. The deck size is incremented.
 *
 * @param[in,out] deck Pointer to the CardDeck.
 * @param[in] c Card to add.
 */
void addCardTop(CardDeck* deck, Card c)
{
    CardNode* node = createNode(c);
    node->next = deck->head;  // Insert before old head
    deck->head = node;        // New head (top of deck)
    deck->size++;             // Increment deck size
}

/**
 * @brief Add card at bottom.
 * @details Traverses the linked list to append the card at the end.
 *          If the deck is empty, the new card becomes the head.
 */
void addCardBottom(CardDeck* deck, Card c)
{
    CardNode* node = createNode(c);

    if (!deck->head) {
        deck->head = node; // First card in empty deck
    }
    else {
        CardNode* cur = deck->head;
        while (cur->next) // Traverse to last node
            cur = cur->next;
        cur->next = node; // Attach new card at end
    }
    deck->size++;   // Increment deck size
}

/**
 * @brief Remove the top card.
 */
int removeTopCard(CardDeck* deck, Card* out)
{
    if (!deck->head)
        return 0;  // Deck is empty, nothing to remove

    CardNode* old = deck->head;
    deck->head = old->next;  // Advance head to next card

    if (out)
        *out = old->card; // Output removed card

    free(old);       // Free old node
    deck->size--;  // Decrement deck size
    return 1;    // Success
}

/**
 * @brief Remove a card at a specific index.
 */
int removeCardAt(CardDeck* deck, int index, Card* out)
{
    if (index < 0 || index >= deck->size || !deck->head)
        return 0;    // Invalid index or empty deck

    if (index == 0)
        return removeTopCard(deck, out); // Delegate to removeTopCard

    CardNode* prev = deck->head;
    for (int i = 0; i < index - 1; i++)
        prev = prev->next;      // Traverse to node before target

    CardNode* target = prev->next;
    prev->next = target->next;  // Bypass target node

    if (out)
        *out = target->card;    // Output removed card

    free(target);     // Free memory
    deck->size--;       // Update size
    return 1;       // Success
}

/**
 * @brief Get number of cards.
 */
int deckSize(const CardDeck* deck)
{
    return deck->size; // Simply return size
}

/**
 * @brief Check if deck empty.
 */
int isDeckEmpty(const CardDeck* deck)
{
    return (deck->size == 0);// True if no cards
}

/**
 * @brief Convert deck to array.
 */
Card* deckToArray(const CardDeck* deck)
{
    if (deck->size == 0)
        return NULL; // Empty deck, nothing to copy

    Card* arr = malloc(sizeof(Card) * deck->size);
    if (!arr) {
        fprintf(stderr, "Memory error in deckToArray()");
        exit(EXIT_FAILURE);
    }

    CardNode* cur = deck->head;
    int i = 0;
    while (cur) {
        arr[i++] = cur->card;    // Copy card to array
        cur = cur->next;         // Move to next node
    }
    return arr;     // Return array
}

/**
 * @brief Create a deck with `packs × 52` cards.
 */
void createCardDeck(CardDeck* deck, int packs)
{
    initCardDeck(deck);          // Start with empty deck
    if (packs <= 0)
        return;                  // No cards to create

    for (int p = 0; p < packs; p++) {
        for (int s = CLUB; s <= DIAMOND; s++) { // Loop through suits
            for (int r = TWO; r <= ACE; r++) {  // Loop through ranks
                Card c;
                c.suit = (Suit)s;
                c.rank = (Rank)r;
                addCardBottom(deck, c);   // Add card to bottom
            }
        }
    }
}

/**
 * @brief Free all memory used by the deck.
 */
void freeCardDeck(CardDeck* deck)
{
    CardNode* cur = deck->head;
    while (cur) {
        CardNode* next = cur->next; // Save next node
        free(cur);   // Free current node
        cur = next;   // Move to next
    }

    deck->head = NULL;  // Reset deck
    deck->size = 0;
}
