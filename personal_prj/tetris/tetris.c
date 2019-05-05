#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define LEFT_WARD 75
#define RIGHT_WARD 77
#define UP_WARD 72
#define DOWN_WARD 80

enum direction {
    NONE,
    LEFT,
    RIGHT,
    DOWN
};
enum blockState {
    EMPTY,
    SOFT_BLOCK,
    HARD_BLOCK,
    WALL,
    DEADLINE
};

struct block {
    int id;
    int rotationState;
    int y, x;
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

void removeCursor() {
    CONSOLE_CURSOR_INFO curinfo;
    curinfo.bVisible = 0;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}
void gotoyx(int y, int x) {
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printMap(enum blockState map[24][12]);
void createRandomBlock(struct block *b);
void drawPreparingBlock(struct block b);
void loadBlock(struct block *preparingBlock, struct block *currentBlock);
void drawBlock(struct block b);
void eraseBlock(struct block b);
void rotateBlock(struct block *b);
int willConflict(enum direction way, enum blockState map[24][12], struct block b);
void moveBlock(enum direction way, enum blockState (*map)[10], struct block *b);
void putBlockToMap(enum blockState (*map)[12], struct block b);
void fixBlock(enum blockState (*map)[12], struct block b);


int main(void){
    struct block preparingBlock, currentBlock;
    int i;

    int map[24][12] = { 0 };

    for(i = 0; i < 12; i++) {
        map[3][i] = DEADLINE;
        map[23][i] = WALL;
    }
    for(i = 0; i < 24; i++){
        map[i][0] = WALL;
        map[i][11] = WALL;
    }
    printMap(map);

    srand(time(NULL));
    createRandomBlock(&preparingBlock);
    loadBlock(&preparingBlock, &currentBlock);
    drawPreparingBlock(preparingBlock);
    drawBlock(currentBlock);

    for(;;){
        if(willConflict(DOWN, map, currentBlock))
            fixBlock(map, currentBlock);
        while(kbhit()){
            eraseBlock(currentBlock);
            switch(getch()){
                case LEFT_WARD:
                    moveBlock(LEFT, map, &currentBlock);
                    break;
                case RIGHT_WARD:
                    moveBlock(RIGHT, map, &currentBlock);
                    break;
                case DOWN_WARD:
                    moveBlock(DOWN, map, &currentBlock);
                    break;
                case UP_WARD:
                    eraseBlock(currentBlock);
                    rotateBlock(&currentBlock);
            }
            drawBlock(currentBlock);
        }
        putBlockToMap(map, currentBlock);
    }

    gotoyx(30, 0);


    return 0;
}

void printMap(enum blockState map[24][12]){
    int i, j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 12; j++) {
            if(map[i][j] == EMPTY)
                printf("  ");
            else if (map[i][j] == SOFT_BLOCK)
                printf("□");
            else if (map[i][j] == HARD_BLOCK)
                printf("■");
            else if (map[i][j] == WALL)
                printf("▒");
        }
        puts("");
    }
}
void createRandomBlock(struct block *b){
    b->id = rand()%7;
    b->rotationState = rand()%4;
    b->y=3;
    b->x=3;
}
void drawPreparingBlock(struct block b){
    int i, j;
    gotoyx(0, 22);
    printf("▒▒▒▒▒▒");
    for(i = 0; i < 4; i++){
        gotoyx(1+i, 22);
        puts("▒        ▒");
    }
    gotoyx(i+1, 22);
    printf("▒▒▒▒▒▒");
    b.y = 1;
    b.x = 12;
    eraseBlock(b);
    drawBlock(b);
}
void loadBlock(struct block *preparingBlock, struct block *currentBlock){
    *currentBlock = *preparingBlock;
    createRandomBlock(preparingBlock);
}
void drawBlock(struct block b, enum blockState type){
    int i, j, yForBlock, xForBlock=0;
    for(i = b.y, yForBlock=0; i< b.y+4; i++, yForBlock++) {
        for (j = b.x*2, xForBlock=0; j < b.x*2+8; j+=2, xForBlock++) {
            gotoyx(i, j);
            if(blockShapes[b.id][b.rotationState][yForBlock][xForBlock] != NONE) {
                switch(type){
                    case SOFT_BLOCK:
                        printf("□");
                        break;
                    case HARD_BLOCK:
                        printf("■");
                }

            }else{
                gotoyx(i, j+2);
            }
        }
    }
}
void eraseBlock(struct block b){
    int i, j, yForBlock, xForBlock=0;
    for(i = b.y, yForBlock=0; i< b.y+4; i++, yForBlock++) {
        for (j = b.x*2, xForBlock=0; j < b.x*2+8; j+=2, xForBlock++) {
            gotoyx(i, j);
            blockShapes[b.id][b.rotationState][yForBlock][xForBlock] == SOFT_BLOCK ? printf("  ") : gotoyx(i, j+2);
        }
    }
}
void rotateBlock(struct block *b){
    b->rotationState++;
    b->rotationState%=4;
}
int willConflict(enum direction way, enum blockState map[24][12], struct block b){
    int i, j, y, x;
    switch(way){
        case LEFT:
            b.x--;
            break;
        case RIGHT:
            b.x++;
            break;
        case DOWN:
            b.y++;
    }
    for(i = b.y, y = 0; i < b.y+4; i++, y++){
        for(j = b.x, x = 0; j < b.x+4; j++, x++){
            if(map[i][j] == 3 && blockShapes[b.id][b.rotationState][y][x]==1){//if wall and falling block conflicts
                return 1;
            }
        }
    }
    return NONE;
}
void moveBlock(enum direction way, enum blockState (*map)[10], struct block *b){
    if(!willConflict(way, *map, *b))
        switch(way){
            case LEFT:
                (b->x)--;
                break;
            case RIGHT:
                (b->x)++;
                break;
            case DOWN:
                (b->y)++;
        }
    putBlockToMap(map, *b);
}
void putBlockToMap(enum blockState (*map)[12], struct block b){
    int i, j, y, x;
    for(i = b.y, y = 0; i < b.y+4; i++, y++){
        for(j = b.x, x = 0; j < b.x+4; j++, x++){
            if(blockShapes[b.id][b.rotationState][y][x] && map[i][j] != 0)
                map[i][j] = blockShapes[b.id][b.rotationState][y][x];
        }
    }
}
void fixBlock(enum blockState (*map)[12], struct block b){
    int i, j, y, x;
    for(i = b.y, y = 0; i < b.y+4; i++, y++){
        for(j = b.x, x = 0; j < b.x+4; j++, x++){
            if(blockShapes[b.id][b.rotationState][y][x] && map[i][j] != 0)
                map[i][j] = HARD_BLOCK;
        }
    }
    eraseBlock(b);
    drawBlock()
}