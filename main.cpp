#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS (NUM_RANKS * NUM_SUITS)
#define NUM_DECKS 2
#define NUM_ROWS 7
#define NUM_COLUMNS 7
#define MAX_UNDO 5

enum suit {
    SPADES,
    HEARTS,
    CLUBS,
    DIAMONDS
};

enum rank {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};

struct card {
    int suit;
    int rank;
    struct card *next;
};

struct deck {
    struct card *top;
};

struct game {
    struct deck stock[NUM_DECKS];
    struct deck waste;
    struct deck foundation[NUM_SUITS];
    struct deck tableau[NUM_ROWS][NUM_COLUMNS];
    struct card *undo_stack[MAX_UNDO];
    int undo_stack_top;
};

void shuffle(struct deck *deck)
{
    struct card *card_array[NUM_CARDS];
    struct card *temp_card;
    int i, j;

    srand(time(NULL));

    // put all the cards into an array
    temp_card = deck->top;
    for (i = 0; i < NUM_CARDS; i++) {
        card_array[i] = temp_card;
        temp_card = temp_card->next;
    }

    // shuffle the array
    for (i = NUM_CARDS - 1; i > 0; i--) {
        j = rand() % (i + 1);
        temp_card = card_array[i];
        card_array[i] = card_array[j];
        card_array[j] = temp_card;
    }

    // rebuild the deck using the shuffled array
    deck->top = card_array[0];
    for (i = 0; i < NUM_CARDS - 1; i++) {
        card_array[i]->next = card_array[i+1];
    }
    card_array[NUM_CARDS-1]->next = NULL;
}

void initialize_deck(struct deck *deck)
{
    struct card *card_ptr;
    int i, j;

    // allocate memory for all the cards in the deck
    deck->top = (struct card *)malloc(NUM_CARDS * sizeof(struct card));
    card_ptr = deck->top;

    // create all the cards in the deck
    for (i = 0; i < NUM_SUITS; i++) {
        for (j = 0; j < NUM_RANKS; j++) {
            card_ptr->suit = i;
            card_ptr->rank = j;
            card_ptr->next = card_ptr + 1;
            card_ptr++;
        }
    }

    // set the last card's next pointer to NULL
    card_ptr--;
    card_ptr->next = NULL;
}

void initialize_game(struct game *game)
{
    int i, j;

    // initialize the decks
    for (i = 0; i < NUM_DECKS; i++) {
        initialize_deck(&game->stock[i]);
    }
    shuffle(&game->stock[0]);
    shuffle(&game->stock[1]);

    // initialize the waste pile
    game->waste.top = NULL;

    // initialize the foundation piles
    for (i = 0; i < NUM_SUITS; i++) {
        game->foundation[i].top = NULL;
    }

    // initialize the tableau piles
    for (i = 0; i < MAX_UNDO; i++) {
        game->undo_stack[i] = NULL;
    }
    game->undo_stack_top = -1;
}

void display_card(struct card *card)
{
    char rank_char;
    char suit_char;
    switch (card->rank) {
        case ACE:
            rank_char = 'A';
            break;
        case TWO:
            rank_char = '2';
            break;
        case THREE:
            rank_char = '3';
            break;
        case FOUR:
            rank_char = '4';
            break;
        case FIVE:
            rank_char = '5';
            break;
        case SIX:
            rank_char = '6';
            break;
        case SEVEN:
            rank_char = '7';
            break;
        case EIGHT:
            rank_char = '8';
            break;
        case NINE:
            rank_char = '9';
            break;
        case TEN:
            rank_char = 'T';
            break;
        case JACK:
            rank_char = 'J';
            break;
        case QUEEN:
            rank_char = 'Q';
            break;
        case KING:
            rank_char = 'K';
            break;
    }

    switch (card->suit) {
        case SPADES:
            suit_char = 'S';
            break;
        case HEARTS:
            suit_char = 'H';
            break;
        case CLUBS:
            suit_char = 'C';
            break;
        case DIAMONDS:
            suit_char = 'D';
            break;
    }

    printf("%c%c", rank_char, suit_char);
}

    void display_deck(struct deck *deck)
    {
    struct card *card_ptr;
        if (deck->top == NULL) {
            printf("  ");
            return;
        }

        card_ptr = deck->top;
        while (card_ptr != NULL) {
            display_card(card_ptr);
            printf(" ");
            card_ptr = card_ptr->next;
        }
    }

void display_game(struct game *game)
{
    int i, j;
    printf("Stock 1: ");
    display_deck(&game->stock[0]);
    printf("\n");
    printf("Stock 2: ");
    display_deck(&game->stock[1]);
    printf("\n");
    printf("Waste: ");
    display_deck(&game->waste);
    printf("\n");
    for (i = 0; i < NUM_SUITS; i++) {
        printf("Foundation %d: ", i+1);
        display_deck(&game->foundation[i]);
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < NUM_ROWS; i++) {
        printf("Tableau %d: ", i+1);
        for (j = 0; j < NUM_COLUMNS; j++) {
            display_deck(&game->tableau[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

int main()
{
    struct game game;
    initialize_game(&game);
    display_game(&game);
    return 0;
}




