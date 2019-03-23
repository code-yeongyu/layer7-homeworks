#include <stdio.h>

int main(void)
{
    int a, b, c, max;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    max = a > b ? a : b;
    max = max > c ? max : c;

    printf("max: %d", max);

    return 0;
}