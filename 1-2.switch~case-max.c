#include <stdio.h>

int main(void)
{
    int a, b, c, max;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    switch (a > b) {
    case 1:
        max = a;
        break;
    default:
        max = b;
    }
    switch (c > max) {
    case 1:
        max = c;
    }

    printf("max: %d", max);

    return 0;
}
