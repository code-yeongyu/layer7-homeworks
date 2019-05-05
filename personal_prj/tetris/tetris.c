#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define LEFT_WARD 75
#define RIGHT_WARD 77
#define FRONT_WARD 72
#define BACK_WARD 80

struct block {
    int id;
    int rotationState;
    int shape[4][4][4];
};

void gotoxy(int x,int y) {
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void createRandomBlock(struct block *b);
void drawBlock(int block[4][4], int y, int x);
void eraseBlock(int y, int x);

int main(void){
    struct block preparingBlock;
    createRandomBlock(&preparingBlock);
    drawBlock(preparingBlock.shape[preparingBlock.rotationState], 0, 0);
    printf("state: %d, id:%d", preparingBlock.rotationState, preparingBlock.id);

    return 0;
}

void createRandomBlock(struct block *b){
    int i, j, k;
    srand(time(NULL));
    b->id = rand()%7;
    b->rotationState = rand()%4;
    const int blockShapes[7][4][4][4] = {
            // ■
            // ■ ■ ■
            0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,    0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,    0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,    0,0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,
            //     ■
            // ■ ■ ■
            0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,    0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,    0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,    0,0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,
            // ■ ■
            // ■ ■
            0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,    0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,    0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,    0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
            // ■ ■ ■ ■
            0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,    0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,    0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,    0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
            //   ■
            // ■ ■ ■
            0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0,    0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,    0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,    0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,
            // ■ ■
            //   ■ ■
            0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,    0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,    0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,    0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,
            //    ■ ■
            //  ■ ■
            0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,    0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,    0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,    0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0
    };
    for(i = 0;i<4;i++)
        for (j = 0; j < 4; j++)
            for(k = 0; k < 4; k++)
                b->shape[i][j][k] = blockShapes[b->id][i][j][k];
}
void drawBlock(int block[4][4], int y, int x){
    int i, j, yForBlock, xForBlock=0;
    for(i = y, yForBlock=0;i<y+4;i++, yForBlock++) {
        for (j = x, xForBlock=0; j < x+8; j+=2, xForBlock++) {
            gotoxy(j, i);
            block[yForBlock][xForBlock] ? printf("■") : gotoxy(j+2, i);
        }
    }
}
void eraseBlock(int y, int x){
    int i, j;
    for(i = y;i<y+3;i++) {
        for (j = x; j <x+8; j+=2) {
            gotoxy(j, i);
            printf("  ");
        }
    }
}