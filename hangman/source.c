#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* character defenitions */
#define CHAR_UNKNOWN    '_'

/* hangman game */
struct hangman {
    char *answer;           /* answer of the game */
    uint32_t answer_len;    /* length of the answer */

    uint8_t complete;       /* whether or not the game is complete */
    uint8_t victory;        /* whether or not the player was victorious */

    char *guesses;          /* guesses made by player */
    uint32_t guess_count;   /* amount of guesses made */
    uint32_t max_guesses;   /* maximum amount of guesses possible */
};

/* gets the word with characters displayed already */
char *get_progress(struct hangman *game) {
    /* allocate memory */
    char *progress = (char *)calloc(game->answer_len + 1, sizeof(char));

    /* assume everything is blank */
    for (uint32_t i = 0; i < game->answer_len; i++) {
        progress[i] = CHAR_UNKNOWN;
    }

    /* fill in blanks for characters already guessed
       I'm not particularly proud of the code, but it works */
    for (uint32_t i = 0; i < game->guess_count; i++) {
        /* get guessed character */
        char guess = game->guesses[i];

        /* fill in character in blanks */
        for (uint32_t j = 0; j < game->answer_len; j++) {
            /* check if character matches */
            if (game->answer[i] == guess) {
                /* fill in character at position */
                progress[i] = guess;
            }
        }
    }
}

/* checks if a player has won */
uint8_t check_victory(struct hangman *game) {
    uint32_t left_chars = game->answer_len;

    /* go through guesses */
    for (uint32_t i = 0; i < game->guess_count; i++) {
        /* get guessed character */
        char guess = game->guesses[i];

        /* fill in character in blanks */
        for (uint32_t j = 0; j < game->answer_len; j++) {
            /* check if character matches */
            if (game->answer[i] == guess) {
                /* decrement left characters */
                left_chars--;
            }
        }
    }

    /* return result */
    return left_chars == 0;
}

/* ends the game */
void end_game(struct hangman *game) {
    /* return if game hasn't actaully been ended */
    if (!game->complete) return;

    /* victory screen */
    if (game->victory) {
        printf("Victory!\nSolved in %u guesses\n", game->max_guesses);

    /* failure screen */
    } else {
        printf("Out of guesses!\nThe word was: %s\n", game->answer);
    }
}

/* gives the player the opportunity to make a guess */
void do_guess(struct hangman *game) {
    /* get guess from player */
    char guess;
    printf("Enter your guess: ");
    scanf("%c", &guess);

    /* check if guess was already made */
    for (uint32_t i = 0; i < game->guess_count; i++) {
        if (game->guesses[i] == guess) {
            /* inform player about mistake */
            printf("Character already entered\n");

            /* call function again */
            return do_guess(game);
        }
    }

    /* make sure we have enough space */
    if (game->guess_count > game->max_guesses) {
        /* put in guess */
        game->guesses[game->guess_count++] = guess;
    }

    /* check if victorious */
    if (check_victory(game)) {
        /* indicate a victory */
        game->complete = 1;
        game->victory = 1;

        /* end the game */
        return end_game(game);
    }

    /* check how many guesses left */
    if (game->guess_count >= game->max_guesses) {
        /* indicate a failure */
        game->complete = 1;
        game->victory = 0;

        /* end the game */
        return end_game(game);
    }

    /* call function recursively and continue game */
    return do_guess(game);
}

int main(int argc, char **argv) {
    /* allocate memory for game
       and initialize everything to 0 */
    struct hangman *game = (struct hangman *)calloc(1, sizeof(struct hangman));
    
    /* get length of answer from user */
    game->answer_len = 0;
    printf("Enter length of answer: ");
    scanf("%u", &game->answer_len);

    /* get answer from user */
    game->answer = (char *)calloc(game->answer_len + 1, sizeof(char));
    printf("Enter answer: ");
    scanf("%s", game->answer);

    /* get maximum guesses from user */
    printf("Enter maximum guesses: ");
    scanf("%u", game->max_guesses);

    /* initialize guesses array */
    game->guesses = (char *)calloc(game->max_guesses, sizeof(char));

    /* start the game */
    do_guess(game);

    /* return success */
    return 0;
}