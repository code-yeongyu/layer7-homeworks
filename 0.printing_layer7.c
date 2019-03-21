#include <stdio.h>

int main(void){
	int height, width, i, j, k, l;

	char line[8][82] = {
		"    *                   *        *       *   *********   *****       **********",
		"    *                  * *        *     *    *           *    *               *",
		"    *                 *   *        *   *     *           *     *             *",
		"    *                *     *        * *      *           *    *             *",
		"    *               *********        *       *********   *****             *",
		"    *              *         *       *       *           **               *",
		"    *             *           *      *       *           * *             *",
		"    ***********  *             *     *       *********   *  *           *"
	};
	printf("Height: ");
	scanf("%d", &height);
	printf("Width: ");
	scanf("%d", &width);

	for(i = 0; i < 8; i++){
		for(l = 0; l < height; l++){
			for(j = 0; j < (int)sizeof(line[i]); j++)
				for(k = 0; k < width; k++)
					printf("%c", line[i][j]);
			printf("\n");
		}
		
		printf("\n");
	}

}
