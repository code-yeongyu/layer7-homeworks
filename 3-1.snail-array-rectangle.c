#include <stdio.h>

int main(void){
	int arr_size_h, arr_size_w;
	printf("ex 1) ");
	scanf("%d %d", &arr_size_h, &arr_size_w);
	int arr[100][100] = { 0 };
	int i = 0, j = 0, num = 1, counter = 0;
	int direction = 0;//0 for right side, 1 for down side, 2 for left side, 3 for up side
	while (num <= arr_size_w*arr_size_h){
		arr[i][j] = num;

		if (direction == 0){
			if (arr[i][j + 1] == 0 && j < arr_size_w-1){
				j++;
				counter = 0;
			}
			else{
				counter++;
				direction = 1;
				i++;
			}
		}//오른쪽으로 진행

		else if (direction == 1){
			if (arr[i + 1][j] == 0 && i < arr_size_h-1){
				i++;
				counter = 0;
			}
			else{
				counter++;
				direction = 2;
				j--;
			}
		}//아래쪽으로 진행

		else if (direction == 2){
			if (arr[i][j-1] == 0 && j > 0){
				j--;
				counter = 0;
			}
			else{
				counter++;
				direction = 3;
				i--;
			}
		}//왼쪽으로 진행

		else if (direction == 3){
			if ( arr[i - 1][j] == 0 && i > 0){
				i--;
				counter = 0;
			}
			else{
				counter++;
				direction = 0;
				j++;
			}
		}//위쪽으로 진행
		num++;
	}

	for (i = 0; i<arr_size_h; i++){
		for (j = 0; j<arr_size_w; j++){
			printf("%3d ", arr[i][j]);
		}
		printf("\n");
	}//출력
	return 0;
}
