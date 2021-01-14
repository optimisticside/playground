#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

/* letters in morse code */
const char *alpha[] = {
    ".-",   /* A */
    "-...", /* B */
    "-.-.", /* C */
    "-..",  /* D */
    ".",    /* E */
    "..-.", /* F */
    "--.",  /* G */
    "....", /* H */
    "..",   /* I */
    ".---", /* J */
    "-.-",  /* K */
    ".-..", /* L */
    "--",   /* M */
    "-.",   /* N */
    "---",  /* O */
    ".--.", /* P */
    "--.-", /* Q */
    ".-.",  /* R */
    "...",  /* S */
    "-",    /* T */
    "..-",  /* U */
    "...-", /* V */
    ".--",  /* W */
    "-..-", /* X */
    "-.--", /* Y */
    "--..", /* Z */
};

/* digits in morse code */
const char *digit[] {
    "-----", /* 0 */
    ".----", /* 1 */
    "..---", /* 2 */
    "...--", /* 3 */
    "....-", /* 4 */
    ".....", /* 5 */
    "-....", /* 6 */
    "--...", /* 7 */
    "---..", /* 8 */
    "----.", /* 9 */
}

/* translates a string to morse code */
char *to_morse(char *str) {
    /* save our result and position */
    uint32_t str_size = strlen(str);
    char **code = (char **)calloc(str_size, sizeof(char *));

    /* go through string */
    for (uint32_t i = 0; i < strlen(str); i++) {
        /* get character */
        char ch = str[i];

        /* if character is alphabetic */
        if (isalpha(ch)) {
            /* allocate morse */
            uint8_t num = strtol(ch) - 'a';
            char *morse = (char *)calloc(strlen(alpha[num])+1, sizeof(char));

            /* get and add mores */
            strcpy(morse, digit[num]);
            code[i] = morse;

        /* if character is digit */
        } else if (isdigit(ch)) {
            /* allocate morse */
            uint8_t num = ch - '0';
            char *morse = (char *)calloc(strlen(digit[num])+1, sizeof(char));

            /* get and add morse */
            strcpy(morse, digit[num]);
            code[i] = morse;
        }
    }

    /* return morse code */
    return code;
}