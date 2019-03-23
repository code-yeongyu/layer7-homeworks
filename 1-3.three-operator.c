#include <stdio.h>

int main(void)
{
    int a, b, c, max, min;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    max = a > b ? a : b;
    max = max > c ? max : c;
    min = a < b ? a : b;
    min = min < c ? min : c;

    printf("max: %d, min: %d", max, min);

    return 0;
}
