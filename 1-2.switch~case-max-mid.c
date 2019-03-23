#include <stdio.h>

int main(void)
{
    int a, b, c, max, min;
    printf("Input(a, b, c): ");
    scanf("%d %d %d", &a, &b, &c);

	switch (a > b) {
    case 1:
            max = a;
            min = b;
            break;
	default:
            max = b;
            min = a;
    }
	switch (c > max) {
    case 1:
        max = c;
    }
	switch (c < min) {
    case 1:
        min = c;
    }

    printf("max: %d, min: %d", max, min);

    return 0;
}
