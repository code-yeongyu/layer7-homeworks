#include <stdio.h>

int main(void) {
    int i, n, sum = 1;
    scanf("%d", &n);
	for (i = 2; i <= n; i++)
        sum *= i;
    printf("%d", sum);
    return 0;
}
