#include <stdio.h>
#include <math.h>
#include <stdint.h>

/* checks if a number is prime or not */
uint8_t check_prime(uint64_t num) {
    /* calculate square root of number */
    uint64_t root = (uint64_t)sqrt(num);

    /* go through possible factors */
    for (uint64_t i = 2; i <= root; i++) {
        /* check if number is divisible */
        if (num % i == 0) {
            /* return false */
            return 0;
        }
    }

    /* no number was found
       so return true */
    return 1;
}

/* gets tne next prime number */
uint64_t next_prime(uint64_t num) {
    /* keep track of our position */
    uint64_t curr = num;

    /* keep searching */
    while (1) {
        /* increment number */
        curr++;

        /* check if number is prime */
        if (check_prime(curr)) {
            /* ruturn number */
            return curr;
        }
    }
}

/* get the amount of digits in a number */
size_t num_digits(uint64_t num) {
    /* keep track of digit count */
    size_t digit_count = 0;

    /* keep adding to digit count */
    while (num > 0) {
        /* divide number by 10 */
        num /= 10;

        /* increment digit count */
        digit_count++;
    }

    /* return digit count */
    return digit_count;
}

int main(int argc, char **argv) {
    /* throw error if invalid args provided */
    if (argc < 2) {
        printf("Invalid arguments provided");
        return -1;
    }

    /* open file */
    FILE *file = fopen(argv[1], "w");

    /* throw error if unable to open file */
    if (!file) {
        printf("Unable to open file\n");
        return -1;
    }

    /* keep track of number and position in file */
    uint64_t file_pos = 0;
    uint64_t curr_num = 2;
    size_t buffer_len = 0;

    /* run through loop */
    while (1) {
        /* calculate next number */
        curr_num = next_prime(curr_num);

        /* allocate stack memory for character buffer */
        buffer_len = num_digits(curr_num) + 1;
        char buffer[buffer_len];

        /* add to buffer */
        sprintf(buffer, "%lu ", curr_num);

        /* append to file */
        fseek(file, 0, file_pos);
        fputs(buffer, file);

        /* increment file position */
        file_pos += buffer_len;
    }

    /* close file */
    fclose(file);

    /* return success */
    return 0;
}