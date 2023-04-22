#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8
void init(void);
void show(void);
void put(char);
int check(void);
int over(void);
int isOk(char, int, int, int, int, int);
int canPut(char, int);
void set(char, int, int, int, int, int, int, int);
void reversi(char, int, int, int, int, int);
void makeStrongPlace1(char);
int cntPlayerInTable(char);
int cntPlayerInTmpTable(char);
void copyTableToTmpTable();
char table[N][N];
char tmpTable[N][N];
char P1 = 'O', P2 = 'X', NO = '-';
int turn = 0;
int strongPlace[2]; // y x
int main(void)
{
    srand((unsigned int)time(NULL));
    init();
    show();
    while (over())
    {
        if (turn % 2 == 0)
            put(P1);
        else
            put(P2);
        show();
        turn++;
    }
    if (1 == check())
        printf("I am a winner!\n");
    else if (0 == check())
        printf("I am a loser...\n");
    else
        printf("I am not neither.\n");
    printf("P1: %d, P2: %d\n", cntPlayerInTable(P1), cntPlayerInTable(P2));
    return 0;
}
int over(void)
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (table[i][j] == NO)
                cnt++;
    if (cnt == 0)
        return 0;
    else
        return 1;
}
void init(void)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            table[i][j] = NO;
    table[N / 2][N / 2] = table[N / 2 - 1][N / 2 - 1] = P1;
    table[N / 2][N / 2 - 1] = table[N / 2 - 1][N / 2] = P2;
}
void show(void)
{
    system("cls");
    printf("turn : %d\nO:P1 X:P2 \nplease input a coordinate. \nex : y x\n", turn);
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            printf("  ");
            for (int j = 0; j < N; j++)
                printf("%d ", j);
            printf("\n");
        }
        for (int j = 0; j < N; j++)
        {
            if (j == 0)
                printf("%d ", i);
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}
int check(void)
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (table[i][j] == P1)
                cnt++;
    if (cnt == N * N / 2)
        return 2;
    else if (cnt > N * N / 2)
        return 1;
    else
        return 0;
}
void put(char player)
{
    int x, y;
    if (!canPut(player, 0))
    {
        show();
        if (player == P1)
            printf("<---------The places can be put didn't exitst! Turnover!----------->\n");
        return;
    }
    while (1)
    {
        // if (player == P1)
        //     scanf("%d %d", &y, &x);
        // // x = rand() % N, y = rand() % N;
        // else
        // {
        //     // y = rand() % N, x = rand() % N;
        //     makeStrongPlace1(player);
        //     y = strongPlace[0];
        //     x = strongPlace[1];
        // }
        makeStrongPlace1(player);
        y = strongPlace[0];
        x = strongPlace[1];
        if (isOk(player, y, x, 0, -1, 0)) // 置き位置として正しいか(範囲内かつ一枚でも相手コマを返せるか)
            break;
        else if (player == P1)
        {
            show();
            printf("<---------The place is not correct! Put again!----------->\n");
        }
    }
    set(player, y, x, 0, 0, 0, -1, 0);
}
int isOk(char player, int y, int x, int flag, int dir, int select) // 行 列　の順で座標置く
{
    char target = player == P1 ? P2 : P1;
    int i, check = 0, dirLib[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    if (x <= -1 || N <= x || y <= -1 || N <= y)
        return 0;
    if (select == 0)
    {
        if (dir == -1)
        {
            if (table[y][x] != NO)
                return 0;
            for (i = 0; i < 8; i++)
                check += isOk(player, y + dirLib[i][0], x + dirLib[i][1], 0, i, 0);
            return check;
        }
        if (table[y][x] == player && flag)
            return 1;
        if (table[y][x] != target)
            return 0;
        else
            return isOk(player, y + dirLib[dir][0], x + dirLib[dir][1], 1, dir, 0);
    }
    else
    {
        if (dir == -1)
        {
            if (tmpTable[y][x] != NO)
                return 0;
            for (i = 0; i < 8; i++)
                check += isOk(player, y + dirLib[i][0], x + dirLib[i][1], 0, i, 1);
            return check;
        }
        if (tmpTable[y][x] == player && flag)
            return 1;
        if (tmpTable[y][x] != target)
            return 0;
        else
            return isOk(player, y + dirLib[dir][0], x + dirLib[dir][1], 1, dir, 1);
    }
}
int canPut(char player, int select)
{
    if (select == 0)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (isOk(player, i, j, 0, -1, 0))
                    return 1;
    }
    else
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (isOk(player, i, j, 0, -1, 1))
                    return 1;
    }
    return 0;
}
void reversi(char player, int y1, int x1, int y2, int x2, int select)
{
    if (y1 > y2)
    {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
        tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (select == 0)
    {
        if (x1 == x2)
        {
            for (int i = y1; i <= y2; i++)
                table[i][x1] = player;
            return;
        }
        if (x1 > x2)
        {
            int tmp = y2;
            y2 = y1;
            y1 = tmp;
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        for (int i = x1; i <= x2; i++)
            table[((y1 - y2) / (x1 - x2)) * i + ((x1 * y2 - x2 * y1) / (x1 - x2))][i] = player;
    }
    else
    {
        if (x1 == x2)
        {
            for (int i = y1; i <= y2; i++)
                tmpTable[i][x1] = player;
            return;
        }
        if (x1 > x2)
        {
            int tmp = y2;
            y2 = y1;
            y1 = tmp;
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }
        for (int i = x1; i <= x2; i++)
            tmpTable[((y1 - y2) / (x1 - x2)) * i + ((x1 * y2 - x2 * y1) / (x1 - x2))][i] = player;
    }
}
void set(char player, int y1, int x1, int y2, int x2, int flag, int dir, int select)
{
    char target = player == P1 ? P2 : P1;
    int i, check = 0, dirLib[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    if (x2 <= -1 || N <= x2 || y2 <= -1 || N <= y2)
        return;
    if (select == 0)
    {
        if (dir == -1)
        {
            for (i = 0; i < 8; i++)
                set(player, y1, x1, y1 + dirLib[i][0], x1 + dirLib[i][1], 0, i, 0);
            return;
        }
        if (table[y2][x2] == player && flag)
        {
            reversi(player, y1, x1, y2, x2, 0);
            return;
        }
        if (table[y2][x2] != target)
            return;
        else
            set(player, y1, x1, y2 + dirLib[dir][0], x2 + dirLib[dir][1], 1, dir, 0);
    }
    else
    {
        if (dir == -1)
        {
            for (i = 0; i < 8; i++)
                set(player, y1, x1, y1 + dirLib[i][0], x1 + dirLib[i][1], 0, i, 1);
            return;
        }
        if (tmpTable[y2][x2] == player && flag)
        {
            reversi(player, y1, x1, y2, x2, 1);
            return;
        }
        if (tmpTable[y2][x2] != target)
            return;
        else
            set(player, y1, x1, y2 + dirLib[dir][0], x2 + dirLib[dir][1], 1, dir, 1);
    }
}
void makeStrongPlace1(char player) // 一番返すことのできる場所をstrongPlace[]に格納する  // playerにとってのstrongPlace[]を作る。
{
    int countPlayerInTable = cntPlayerInTable(player), countPlayerInTmpTable, tmpStrongPlace[3] = {0, 0, 0}; // y x 返せる数 で保管する
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            copyTableToTmpTable();
            if (isOk(player, i, j, 0, -1, 1))
                set(player, i, j, 0, 0, 0, -1, 1);
            countPlayerInTmpTable = cntPlayerInTmpTable(player);
            if (tmpStrongPlace[2] < (countPlayerInTmpTable - countPlayerInTable))
            {
                tmpStrongPlace[0] = i;
                tmpStrongPlace[1] = j;
                tmpStrongPlace[2] = countPlayerInTmpTable - countPlayerInTable;
            }
        }
    }
    strongPlace[0] = tmpStrongPlace[0];
    strongPlace[1] = tmpStrongPlace[1];
}
int cntPlayerInTmpTable(char player)
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (tmpTable[i][j] == player)
                cnt++;
        }
    }
    return cnt;
}
int cntPlayerInTable(char player)
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (table[i][j] == player)
                cnt++;
        }
    }
    return cnt;
}
void copyTableToTmpTable()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tmpTable[i][j] = table[i][j];
}
// isOk(player, y, x, 0, -1, 0)でtable[][]をみる。isOk(player, y, x, 0, -1, 1)でtable[][]をみる。置くな！なら0を返す。
// set(player, y, x, 0, 0, 0, -1, 0)でtable[][]を返す。set(player, y, x, 0, 0, 0, -1, 1)でtmpTable[][]を返す。