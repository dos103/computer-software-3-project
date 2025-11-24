#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Card.h"
#include "CardDeck.h"

 /* pause function */
void wait_for_enter(void)
{
    printf("Press ENTER to continue...");
    while (getchar() != '\n')
        ;
}

/* display a player's hand */
void print_player_hand(int player_num, CardDeck* player)
{
    printf("Player %d's cards:\n", player_num);
    for (int i = 0; i < player->size; i++) {
        card_print(player->cards[i], 1);
    }
    printf("\n");
}

/* first matching card index, or -1 */
int find_matching_card(CardDeck* p, Card top)
{
    for (int i = 0; i < p->size; i++) {
        if (card_matches(p->cards[i], top))
            return i;
    }
    return -1;
}

/* move played card to played deck and display */
void play_card(int player_num, CardDeck* player, CardDeck* played, int index)
{
    Card c;
    carddeck_remove_at(player, index, &c);
    carddeck_push_top(played, c);

    printf("Player %d played %s\n", player_num, card_to_string(c));
    print_player_hand(player_num, player);
}

/* handle drawing a card */
void draw_card(int player_num, CardDeck* hidden, CardDeck* player)
{
    Card drawn;

    carddeck_pop_top(hidden, &drawn);
    printf("Player %d picks %s from hidden deck.\n", player_num, card_to_string(drawn));

    carddeck_push_top(player, drawn);
    carddeck_sort(player);

    print_player_hand(player_num, player);
}

/* refill hidden deck when empty */
void refill_if_needed(CardDeck* hidden, CardDeck* played)
{
    if (!carddeck_is_empty(hidden))
        return;

    printf("\n*** Hidden deck empty — refilling and shuffling ***\n");

    /* last played card stays */
    Card last;
    carddeck_pop_top(played, &last);

    CardDeck temp;
    carddeck_init(&temp);

    Card c;
    while (carddeck_pop_top(played, &c)) {
        carddeck_push_top(&temp, c);
    }

    /* temp now contains all played cards except last */
    carddeck_shuffle(&temp);

    /* move shuffled back to hidden */
    while (!carddeck_is_empty(&temp)) {
        carddeck_pop_top(&temp, &c);
        carddeck_push_top(hidden, c);
    }

    /* restore last card to played deck */
    carddeck_push_top(played, last);

    carddeck_free(&temp);
}

/* ---------------- MAIN GAME LOOP ---------------- */

int main(void)
{
    CardDeck hidden, played, p1, p2;
    int packs;

    carddeck_init(&hidden);
    carddeck_init(&played);
    carddeck_init(&p1);
    carddeck_init(&p2);

    printf("Enter number of packs (each 52 cards): ");
    scanf_s("%d", &packs);

    while (getchar() != '\n');  /* clear input buffer */

    /* create ordered deck */
    carddeck_init_packs(&hidden, packs);

    /* shuffle */
    printf("\nShuffling deck...\n");
    carddeck_shuffle(&hidden);

    /* deal 8 cards each, alternating */
    printf("Dealing cards...\n");
    for (int i = 0; i < 8; i++) {
        Card c1, c2;
        carddeck_pop_top(&hidden, &c1);
        carddeck_push_top(&p1, c1);

        carddeck_pop_top(&hidden, &c2);
        carddeck_push_top(&p2, c2);
    }

    /* sort hands */
    carddeck_sort(&p1);
    carddeck_sort(&p2);

    /* print hands */
    print_player_hand(1, &p1);
    print_player_hand(2, &p2);

    wait_for_enter();

    /* start game */
    printf("Starting game...\n");

    /* flip top card to start played pile */
    Card top;
    carddeck_pop_top(&hidden, &top);
    carddeck_push_top(&played, top);
    printf("Initial card: %s\n\n", card_to_string(top));

    wait_for_enter();

    /* game loop */
    int turn = 1;

    while (1) {
        Card current_top = played.cards[played.size - 1];
        int index;

        if (turn == 1) {
            printf("\n--- Player 1's turn ---\n");
            index = find_matching_card(&p1, current_top);

            if (index >= 0)
                play_card(1, &p1, &played, index);
            else {
                printf("Player 1 cannot play.\n");
                draw_card(1, &hidden, &p1);
            }

            if (p1.size == 0) {
                printf("Player 1 wins!\n");
                break;
            }
        }
        else {
            printf("\n--- Player 2's turn ---\n");
            index = find_matching_card(&p2, current_top);

            if (index >= 0)
                play_card(2, &p2, &played, index);
            else {
                printf("Player 2 cannot play.\n");
                draw_card(2, &hidden, &p2);
            }

            if (p2.size == 0) {
                printf("Player 2 wins!\n");
                break;
            }
        }

        refill_if_needed(&hidden, &played);

        wait_for_enter();
        turn = (turn == 1 ? 2 : 1);
    }

    /* cleanup */
    carddeck_free(&hidden);
    carddeck_free(&played);
    carddeck_free(&p1);
    carddeck_free(&p2);

    return 0;
}
