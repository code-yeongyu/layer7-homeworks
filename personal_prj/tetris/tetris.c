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
};

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

void gotoxy(int y,int x) {
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void createRandomBlock(struct block *b);
void drawBlock(int block[4][4], int y, int x);
void eraseBlock(int y, int x);
void rotateBlock(struct block *b);
void move_block(int (*map)[10], int block[4][4], enum direction d, int y, int x);

int main(void){
    return 0;
}

void createRandomBlock(struct block *b){
    int i, j, k;
    srand(time(NULL));
    b->id = rand()%7;
    b->rotationState = rand()%4;
}
void drawBlock(int block[4][4], int y, int x){
    int i, j, yForBlock, xForBlock=0;
    for(i = y, yForBlock=0;i<y+4;i++, yForBlock++) {
        for (j = x, xForBlock=0; j < x+8; j+=2, xForBlock++) {
            gotoxy(i, j);
            block[yForBlock][xForBlock] ? printf("■") : gotoxy(i, j+2);
        }
    }
}
void eraseBlock(int y, int x){
    int i, j;
    for(i = y;i<y+3;i++) {
        for (j = x; j <x+8; j+=2) {
            gotoxy(i, j);
            printf("  ");
        }
    }
}
void rotateBlock(struct block *b){
    b->rotationState++;
    b->rotationState%=4;
}

