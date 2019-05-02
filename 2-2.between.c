#include <stdio.h>

int main(void)
{
    int a, b, i, sum = 0;
	scanf("%d %d", &a, &b);
	for (i = a; i <= b; i++) {
        if (i % 2) {//홀수
			sum += i;
			printf("+");
		}
        else{
            sum -= i;
			printf("-");
		}
		printf("%d", i);
    }
        printf("=%d", sum);
}
