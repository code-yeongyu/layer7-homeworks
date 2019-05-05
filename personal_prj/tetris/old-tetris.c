#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#define LEFT_WARD 75
#define RIGHT_WARD 77
#define FRONT_WARD 72
#define BACK_WARD 80

enum direction {
    LEFT,
    RIGHT,
    BOTTOM
};

/*
to-do:
    블럭 생성
    블럭 회전
    맵/블럭 출력

    블럭 하 / 좌 / 우 이동, 0에 대한 처리, 1초마다 밑으로 이동 반복

    다음 블록 보여주기

	다음 블록
    블록 내리기 -> 다음 블록 로드하기
    점수
    떨어지는 속도 점수에 따라 가속화
    줄 파괴 -> 칸 내리기
    21칸 이상으로 블럭 쌓임 -> 종료

*/

struct block {
    int id;
    int shape[4][4];
};



const int blocks[7][4][4][4] = {
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
int block_id = -1;

void gotoxy(int x,int y) {
    COORD pos={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void print_shape(){
    int i, j;
    for(i = 0; i < 20;i++){
        printf("                    ■%2d", i);
        puts("");
    }
    printf("■■■■■■■■■■■\n", i);
    for(i = 0;i<10;i++)
        printf("%2d", i);
    gotoxy(0,22);
}

void printMap(int map[24][10]){
    int i, j;
    for(i = 0; i<24;i++){
        for(j = 0;j<10;j++){
            printf("%2d", map[i][j]);
        }
        puts("");
    }
}

void random_block(struct block *b);
void rotate_block(int (*block)[4]);
void load_next_block(struct block *b);
void load_current_block(struct block preparing_block, struct block *current_block);
void put_block_to_map(int (*map)[10], int block[4][4], int from_y, int from_x, int to_y, int to_x);
void print_block(int block[4][4], int from_y, int from_x, int to_y, int to_x);
void erase_block(int from_y, int from_x, int to_y, int to_x);
void move_block(int (*map)[10], int block[4][4], enum direction d, int current_from_y, int current_from_x, int to_y, int to_x);
int will_conflict(int map[24][10], int block[4][4], int block_y, int block_x, enum direction d);

int main(void){
    int map[24][10] = { 0 }; // +4 for detecting game over
    int i, j;
    struct block preparing_block;
    struct block current_block;
    print_shape();

    int x=3,y=3;

    load_next_block(&preparing_block);
    load_current_block(preparing_block, &current_block);



    for(i = 0; ;i++){
        Sleep(300);
        int a = will_conflict(map, current_block.shape, y+i+3, x, BOTTOM);
        if(a)
            return a;
        put_block_to_map(map, current_block.shape, y+i, x, y+i+3, x+3);
        gotoxy(0, 25);
        printMap(map);

        move_block(map, current_block.shape, BOTTOM, y+i, x, y+i+3, x+3);
        gotoxy(0, 22);
        printf("%d번째 이동\n", i+1);
    }

    gotoxy(0, 22);



    return 0;
}

void random_block(struct block *b){
    int i, j;
    srand(time(NULL));
    b->id = rand()%7;
    const int blocks_shape[7][4][4] = {
            {
                    {0, 0, 0, 0},
                    {1, 0, 0, 0},
                    {1, 1, 1, 0},
                    {0, 0, 0, 0}
            },
            {
                    {0, 0, 0, 0},
                    {0, 0, 1, 0},
                    {1, 1, 1, 0},
                    {0, 0, 0, 0}
            },
            {
                    {0, 0, 0, 0},
                    {0, 1, 1, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0}
            },
            {
                    {0, 0, 0, 0},
                    {1, 1, 0, 0},
                    {0, 1, 1, 0},
                    {0, 0, 0, 0}
            },
            {
                    {0, 0, 0, 0},
                    {0, 1, 1, 0},
                    {0, 1, 1, 0},
                    {0, 0, 0, 0}
            },
            {
                    {0, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 1, 0},
                    {0, 1, 0, 0}
            },
            {
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0},
                    {0, 1, 0, 0}
            }
    };
    for(i = 0;i<4;i++)
        for (j = 0; j < 4; j++)
            b->shape[i][j] = blocks_shape[b->id][i][j];
}
void rotate_block(int (*block)[4]){
    if(block_id == 4)
        return;
    int i, j;

    int temp[4][4];

    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            temp[j][3 - i] = block[i][j];


    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            block[i][j] = temp[i][j];

}
void load_next_block(struct block *b){
    int i;
    random_block(b);

    srand(time(NULL));
    int random = rand()%4;

    for(i = 0;i < random; i++)
        rotate_block(b->shape);
}
void load_current_block(struct block preparing_block, struct block *current_block){
    int i, j;
    current_block->id = preparing_block.id;
    for(i = 0;i<4;i++)
        for (j = 0; j < 4; j++)
            current_block->shape[i][j] = preparing_block.shape[i][j];
}
void put_block_to_map(int (*map)[10], int block[4][4], int from_y, int from_x, int to_y, int to_x){
    int i, j, x, y; //i for y, j for x
    for(i = from_y, y=0;i<=to_y;i++, y++)
        for(j = from_x, x=0;j<=to_x;j++, x++)
            map[i][j] = block[y][x];
}
void print_block(int block[4][4], int from_y, int from_x, int to_y, int to_x){
    int i, j, y=0, x=0;
    from_x*=2;
    to_x=from_x+3;
    for(i = from_y;i<=to_y;i++) {
        for (j = from_x; j <= to_x*2-from_x; j+=2) {
            gotoxy(j, i);
            if(block[y][x])
                printf("■");
            else
                gotoxy(j+2, i);
            x++;
        }
        x=0;
        y++;
    }
}
void erase_block(int from_y, int from_x, int to_y, int to_x){
    int i, j;
    from_x*=2;
    to_x=from_x+3;
    for(i = from_y;i<=to_y;i++) {
        for (j = from_x; j <= to_x*2-from_x; j+=2) {
            gotoxy(j, i);
            printf("  ");
        }
        puts("");
    }
}
void move_block(int (*map)[10], int block[4][4], enum direction d, int current_from_y, int current_from_x, int to_y, int to_x){
    int i, j, y=0, x=0, count_zero = 0;
    switch(d){//can be optimizable
        case LEFT:
            for(i = current_from_y;i<=to_y;i++) {
                for (j = current_from_x; j <= to_x; j++) {
                    map[i][j] = 0;
                    map[i][j-1] = block[x][y];
                    x++;
                }
                x=0;
                y++;
            }
            erase_block(current_from_y, current_from_x, to_y, to_x);
            print_block(block, current_from_y, current_from_x-1, to_y, to_x-1);
            break;
        case RIGHT:
            for(i = current_from_y;i<=to_y;i++) {
                for (j = current_from_x; j <= to_x; j++) {
                    map[i][j] = 0;
                    map[i][j+1] = block[x][y];
                    x++;
                }
                x=0;
                y++;
            }
            erase_block(current_from_y, current_from_x, to_y, to_x);
            print_block(block, current_from_y, current_from_x+1, to_y, to_x+1);
            break;
        case BOTTOM:
            for(i = current_from_y;i<=to_y;i++) {
                for (j = current_from_x; j <= to_x; j++) {
                    map[i][j] = 0;
                    map[i+1][j] = block[x][y];
                    x++;
                }
                x=0;
                y++;
            }
            erase_block(current_from_y, current_from_x, to_y, to_x);
            print_block(block, current_from_y+1, current_from_x, to_y+1, to_x);
    }
}
int will_conflict(int map[24][10], int block[4][4], int block_y, int block_x, enum direction d){ //밑으로 내릴때는 y에 to_x를 넣어주어야 함.

    int i, j, count, temp=0;
    switch(d){//can be optimizable
        case LEFT:
            if(block_x==0)
                return 1;
            for(i = block_y;i<=block_y;i++, temp++)
                if(block[temp][0])//if conflict
                    return 2;
            break;
        case RIGHT:
            if(block_x==9)
                return 3;
            for(i = block_y;i<=block_y;i++, temp++)
                if(map[i][block_x+1])//if conflict
                    return 4;
            break;
        case BOTTOM:
            if(block_y==19)
                return 5;
            for(i = block_x;i<=block_x+4;i++){
                if(map[block_y+1][i])//if conflict
                {
                    system("cls");
                    printf("%d %d: %d", block_y+1, i, map[block_y+1][i]);

                    printMap(map);
                    return 6;
                }
                temp++;
            }
    }
    return 0;
}