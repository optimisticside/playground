#include <stdio.h>

/* ackermann function */
int ack(int a, int b) {
    /* when a is 0 */
    if (!a) return b + 1;

    /* when b is 0 */
    if (!b) return ack(a - 1, 1);

    /* default case */
    return ack(a - 1, ack(a, b - 1));
}

int main(int argc, char **argv) {
    while (1) {
        /* get a */
        int a;
        printf("Enter a: ");
        scanf("%d", &a);

        /* get b */
        int b;
        printf("Enter b: ");
        scanf("%d", &b);

        /* calculate */
        int res = ack(a, b);

        /* print result */
        printf("Ackermann of %d and %d is %d", a, b, res);
    }
}