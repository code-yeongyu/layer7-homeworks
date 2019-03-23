#include <stdio.h>

int main(void)
{
    int a, b, c, max;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

    if (a > b)
        max = a;
    else
        max = b;
    if (c > max)
        max = c;

    printf("max: %d", max);

    return 0;
}
