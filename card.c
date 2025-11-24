#include <stdio.h>
#include "Card.h"

 /* Internal arrays for names */
static const char* suit_names[] = {
    "Club",
    "Diamond",
    "Heart",
    "Spade"
};

static const char* rank_names[] = {
    /* index 0-1 unused to align with enum numeric ranks starting at 2 */
    NULL,
    NULL,
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King",
    "Ace"
};

/* Create a Card */
Card card_create(CardSuit suit, CardRank rank)
{
    Card c;
    c.suit = suit;
    c.rank = rank;
    return c;
}

/* Convert to string. Uses static buffer overwritten on each call. */
const char* card_to_string(Card c)
{
    static char buf[32];
    const char* suit_str = "UnknownSuit";
    const char* rank_str = "UnknownRank";

    if (c.suit >= CLUB && c.suit <= SPADE) {
        suit_str = suit_names[c.suit];
    }

    /* rank enum values start at 2 */
    if ((int)c.rank >= 2 && (int)c.rank <= 14) {
        rank_str = rank_names[(int)c.rank];
    }

    /* format "Spade-Five" */
    snprintf(buf, sizeof(buf), "%s-%s", suit_str, rank_str);
    return buf;
}

/* Print a card to stdout; newline if requested */
void card_print(Card c, int newline)
{
    const char* s = card_to_string(c);
    if (newline) {
        printf("%s\n", s);
    }
    else {
        printf("%s", s);
    }
}

/* Return 1 if suits or ranks match */
int card_matches(Card a, Card b)
{
    if (a.suit == b.suit) {
        return 1;
    }
    if (a.rank == b.rank) {
        return 1;
    }
    return 0;
}

/* Compare two cards for ordering (suit then rank) */
int card_compare(const Card* a, const Card* b)
{
    if (a->suit != b->suit) {
        return (int)a->suit - (int)b->suit;
    }
    /* rank numeric comparison (RANK_TWO..RANK_ACE) */
    return (int)a->rank - (int)b->rank;
}
