#include <stdio.h>

int main(void)
{
    int a, b, c, min;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    switch (a < b) {
    case 1:
        min = a;
        break;
    default:
        min = b;
    }
    switch (c < min) {
    case 1:
        min = c;
    }

    printf("min: %d", min);

    return 0;
}