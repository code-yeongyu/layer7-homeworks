#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
        0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        //     ■
        // ■ ■ ■
        0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
        // ■ ■
        // ■ ■
        0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        // ■ ■ ■ ■
        0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
        //   ■
        // ■ ■ ■
        0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0,
        // ■ ■
        //   ■ ■
        0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        //    ■ ■
        //  ■ ■
        0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
};

void gotoyx(int y, int x)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printMap(enum blockState (*map)[12]);
void createRandomBlock(struct block* b);
void drawPreparingBlock(struct block b);
void drawBlock(struct block b, enum blockState type);
void eraseBlock(struct block b);
int willRotateConflict(enum blockState map[24][12], struct block b);
int willMoveConflict(enum direction way, enum blockState map[24][12], struct block b);
void moveBlock(enum direction way, struct block* b);
void putBlockToMap(enum blockState (*map)[12], struct block b);
void destroyLine(enum blockState (*map)[12], int line);
void scoreIfAble(enum blockState (*map)[12], int y);


int main(void)
{
    int i, j, x, y, timer;
    struct block preparingBlock, currentBlock;
    enum blockState map[24][12] = { EMPTY };

    CONSOLE_CURSOR_INFO Curinfo;
    Curinfo.dwSize = 1;
    Curinfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Curinfo);
    //removing cursor

    srand(time(NULL));

    /*setting up stage*/
    for (i = 0; i < 12; i++) {
        map[23][i] = WALL;
    }
    for (i = 0; i < 24; i++) {
        map[i][0] = WALL;
        map[i][11] = WALL;
    }
    /*setting up stage*/

    printMap(map);

    createRandomBlock(&preparingBlock);

    for (;;) {
        currentBlock = preparingBlock;
        createRandomBlock(&preparingBlock);
        drawPreparingBlock(preparingBlock);
        drawBlock(currentBlock, SOFT_BLOCK);
        for (;;) {
            timer = clock();
            while (clock() - timer < 1000) {
                while (kbhit()) {
                    eraseBlock(currentBlock);
                    switch (getch()) {
                        case LEFT_WARD: //move left
                            if (!willMoveConflict(LEFT, map, currentBlock))
                                moveBlock(LEFT, &currentBlock);
                            break;
                        case RIGHT_WARD: //move right
                            if (!willMoveConflict(RIGHT, map, currentBlock))
                                moveBlock(RIGHT, &currentBlock);
                            break;
                        case DOWN_WARD: //move down
                            if (!willMoveConflict(DOWN, map, currentBlock))
                                moveBlock(DOWN, &currentBlock);
                            break;
                        case UP_WARD: //change block
                            if (!willRotateConflict(map, currentBlock)) {
                                eraseBlock(currentBlock);
                                currentBlock.rotationState++;
                                currentBlock.rotationState %= 4;
                            }
                    }
                    drawBlock(currentBlock, SOFT_BLOCK);
                    putBlockToMap(map, currentBlock);
                }
            }
            if (willMoveConflict(DOWN, map, currentBlock)) { //fixing block
                for (i = currentBlock.y, y = 0; i < currentBlock.y + 4; i++, y++) {
                    for (j = currentBlock.x, x = 0; j < currentBlock.x + 4; j++, x++) {
                        if (blockShapes[currentBlock.id][currentBlock.rotationState][y][x])
                            map[i][j] = HARD_BLOCK;
                    }
                }
                eraseBlock(currentBlock);
                drawBlock(currentBlock, HARD_BLOCK);
                scoreIfAble(map, currentBlock.y);
                break;
            } else { //moving block down
                eraseBlock(currentBlock);
                moveBlock(DOWN, &currentBlock);
                drawBlock(currentBlock, SOFT_BLOCK);
                putBlockToMap(map, currentBlock);
            }
        }
    }

    gotoyx(30, 0);

    return 0;
}

void printMap(enum blockState (*map)[12]){
    int i, j;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 12; j++) {
            if (map[i][j] == EMPTY)
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

void createRandomBlock(struct block* b)
{
    b->id = rand() % 7;
    b->rotationState = rand() % 4;
    b->y = 3;
    b->x = 3;
}
void drawPreparingBlock(struct block b)
{
    int i, j;
    gotoyx(0, 22);
    printf("▒▒▒▒▒▒");
    for (i = 0; i < 4; i++) {
        gotoyx(1 + i, 22);
        puts("▒        ▒");
    }
    gotoyx(i + 1, 22);
    printf("▒▒▒▒▒▒");
    b.y = 1;
    b.x = 12;
    eraseBlock(b);
    drawBlock(b, SOFT_BLOCK);
}
void drawBlock(struct block b, enum blockState type)
{
    int i, j, yForBlock, xForBlock = 0;
    for (i = b.y, yForBlock = 0; i < b.y + 4; i++, yForBlock++)
        for (j = b.x * 2, xForBlock = 0; j < b.x * 2 + 8; j += 2, xForBlock++) {
            gotoyx(i, j);
            if (blockShapes[b.id][b.rotationState][yForBlock][xForBlock] != NONE)
                switch (type) {
                    case SOFT_BLOCK:
                        printf("□");
                        break;
                    case HARD_BLOCK:
                        printf("■");
                }
            else
                gotoyx(i, j + 2);
        }
}
void eraseBlock(struct block b)
{
    int i, j, y, x;
    for (i = b.y, y = 0; i < b.y + 4; i++, y++)
        for (j = b.x * 2, x = 0; j < b.x * 2 + 8; j += 2, x++) {
            gotoyx(i, j);
            blockShapes[b.id][b.rotationState][y][x] == SOFT_BLOCK ? printf("  ") : gotoyx(i, j + 2);
        }
}
int willRotateConflict(enum blockState map[24][12], struct block b)
{
    int i, j, y, x;
    b.rotationState++;
    b.rotationState %= 4;
    for (i = b.y, y = 0; i < b.y + 4; i++, y++) {
        for (j = b.x, x = 0; j < b.x + 4; j++, x++) {
            if (map[i][j] != 0 && blockShapes[b.id][b.rotationState][y][x] != 0) { //if wall and falling block conflicts
                return 1;
            }
        }
    }
    return 0;
}
int willMoveConflict(enum direction way, enum blockState map[24][12], struct block b)
{
    int i, j, y, x;
    switch (way) {
        case LEFT:
            b.x--;
            break;
        case RIGHT:
            b.x++;
            break;
        case DOWN:
            b.y++;
    }
    for (i = b.y, y = 0; i < b.y + 4; i++, y++) {
        for (j = b.x, x = 0; j < b.x + 4; j++, x++) {
            if (map[i][j] != 0 && blockShapes[b.id][b.rotationState][y][x] == 1) { //if wall and falling block conflicts
                return 1;
            }
        }
    }
    return NONE;
}
void moveBlock(enum direction way, struct block* b)
{
    switch (way) {
        case LEFT:
            (b->x)--;
            break;
        case RIGHT:
            (b->x)++;
            break;
        case DOWN:
            (b->y)++;
    }
}
void putBlockToMap(enum blockState (*map)[12], struct block b)
{
    int i, j, y, x;
    for (i = b.y, y = 0; i < b.y + 4; i++, y++) {
        for (j = b.x, x = 0; j < b.x + 4; j++, x++) {
            if (blockShapes[b.id][b.rotationState][y][x] && map[i][j] != 0)
                map[i][j] = blockShapes[b.id][b.rotationState][y][x];
        }
    }
}
void destroyLine(enum blockState (*map)[12], int line){
    int i, j;
    for(i = line; i != 2;i--)
        for(j = 1; j <= 10; j++){
            map[i][j] = map[i-1][j];
        }
}
void scoreIfAble(enum blockState (*map)[12], int y){
    int i, j, counter;
    for(i = y; i < y+4; i++){
        for(j = 1, counter=0; j <= 10; j++) {
            if(map[i][j] == HARD_BLOCK)
                counter++;
        }
        if(counter == 10){
            destroyLine(map, i);
            system("cls");
            printMap(map);
        }
    }
}


/*
    todo:
        파괴된 것에 따라 재 출력
        점수
        떨어지는 속도 줄이기
        사망
*/