//
// Created by josef on 05-05-2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants
#define NUM_SUITS 4
#define CARDS_PER_SUIT 13
#define NUM_CARDS (NUM_SUITS * CARDS_PER_SUIT)
#define MAX_LINE_LENGTH 3
#define MAX_FILENAME_LENGTH 255


    deck_t load_deck_from_file(char filename[255]);
        void print_card(card_t card);
void print_deck(deck_t deck);
void print_game(game_t game);
deck_t load_deck_from_file(char* filename);
void shuffle_deck_interleaved(deck_t* deck, int split);
void shuffle_deck_random(deck_t* deck);
void save_deck_to_file(deck_t deck, char* filename);
int get_card_value(card_t card);
int is_valid_move(card_t src_card, card_t dest_card);
void move_card(game_t* game, int src_stack, int dest_stack);
int check_win_condition(game_t game);


// Enums
typedef enum {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
} suit_t;

typedef enum {
    ACE = 1,
    JACK = 11,
    QUEEN = 12,
    KING = 13
} rank_t;

// Structs
typedef struct {
    suit_t suit;
    rank_t rank;
} card_t;

typedef struct {
    card_t cards[NUM_CARDS];
    int top_card_index;
} deck_t;

typedef struct {
    deck_t deck;
    card_t foundation_stacks[NUM_SUITS][CARDS_PER_SUIT];
    card_t tableau_stacks[7][20];
} game_t;


