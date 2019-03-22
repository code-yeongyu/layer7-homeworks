#include <stdio.h>

int main(void){
	int a, b, c, max, min;
	printf("Input(a, b, c): ");
	scanf("%d %d %d", &a, &b, &c);
	
	if(a > b){
		max = a;
		min = b;
	}else{
		max = b;
		min = a;
	}
	if(c > max)
		max = c;
	else if(c < min)
		min = c;

	printf("max: %d, min: %d", max, min);

	return 0;
}
