#include <stdio.h>

int main(void)
{
    int a, b, c, min;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    min = a < b ? a : b;
    min = min < c ? min : c;

    printf("min: %d", min);

    return 0;
}