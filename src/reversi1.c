#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8
void init();
void show();
void put(char);
int check();
void set(char, int, int);
int isitOK(char, int, int);
int whereareyou(int, int);
void reversi(char, int, int, int, int);
int over();
int canPut(char);

char table[N][N];
char ME = 'O', YOU = 'X', NO = '-';
int turn = N * N;

int main()
{
    srand((unsigned int)time(NULL));
    init();
    show();
    while (over())
    {
        if (turn % 2 == 0)
            put(ME);
        else
            put(YOU);
        show();
    }
    if (1 == check())
        printf("I am a winner!\n");
    else if (0 == check())
        printf("I am a loser...\n");
    else
        printf("I am not neither.");
    return 0;
}
int over()
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
void init()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            table[i][j] = NO;
    table[N / 2][N / 2] = table[N / 2 - 1][N / 2 - 1] = ME;
    table[N / 2][N / 2 - 1] = table[N / 2 - 1][N / 2] = YOU;
}
void show()
{
    system("cls");
    printf("turn : %d\nO:ME X:AI \nplease input a coordinate. \nex : x y\n", N * N - turn);
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
int check()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (table[i][j] == ME)
                cnt++;
    if (cnt == N * N / 2)
        return 2;
    else if (cnt > N * N / 2)
        return 1;
    else
        return 0;
}
int canPut(char player)
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (isitOK(player, i, j))
                return 1;
    return 0;
}
void put(char player)
{
    int x, y;
    while (1)
    {
        if (player == ME)
            // scanf("%d %d", &x, &y);
            x = rand() % N, y = rand() % N;
        else
            x = rand() % N, y = rand() % N;

        if (isitOK(player, x, y))
            break;
        else if (canPut(player))
        {
            show();
            printf("<---------The places can put didn't exitst! Turnover!----------->\n");
            return;
        }
        else if (player == ME)
        {
            show();
            printf("<---------The place is not correct! Put again!----------->\n");
        }
    }
    set(player, x, y);
    turn--;
}
int isitOK(char player, int x, int y)
{
    int i, j, f1 = 0, f2 = 0;
    char enm = player == ME ? YOU : ME;
    int h = whereareyou(x, y);
    if (x >= N || y >= N || x < 0 || y < 0 || table[y][x] != NO)
        return 0;
    for (i = -1; i < 2; i++)
        for (j = -1; j < 2; j++)
        {
            if (y + i < 0 || x + j < 0)
                continue;
            if (table[y + i][x + j] == enm)
                f1 = 1;
        }
    if (f1 == 0)
        return 0;
    if (table[y - 1][x] == enm && (h == 1 || h == 3 || h == 4 || h == 5 || h == 7 || h == 8))
        for (i = y - 2; i >= 0; i--)
        {
            if (table[i][x] == NO)
                break;
            if (table[i][x] == player)
                f2 = 1;
        }
    if (table[y + 1][x] == enm && (h == 1 || h == 2 || h == 3 || h == 5 || h == 6 || h == 9))
        for (i = y + 2; i < N; i++)
        {
            if (table[i][x] == NO)
                break;
            if (table[i][x] == player)
                f2 = 1;
        }
    if (table[y][x - 1] == enm && (h == 1 || h == 2 || h == 3 || h == 4 || h == 6 || h == 7))
        for (i = x - 2; i >= 0; i--)
        {
            if (table[y][i] == NO)
                break;
            if (table[y][i] == player)
                f2 = 1;
        }
    if (table[y][x + 1] == enm && (h == 1 || h == 2 || h == 4 || h == 5 || h == 8 || h == 9))
        for (i = x + 2; i < N; i++)
        {
            if (table[y][i] == NO)
                break;
            if (table[y][i] == player)
                f2 = 1;
        }
    if (table[y - 1][x - 1] == enm && (h == 1 || h == 3 || h == 4 || h == 7))
        for (i = 2; y - i >= 0 && x - i >= 0; i++)
        {
            if (table[y - i][x - i] == NO)
                break;
            if (table[y - i][x - i] == player)
                f2 = 1;
        }
    if (table[y + 1][x + 1] == enm && (h == 1 || h == 2 || h == 5 || h == 9))
        for (i = 2; y + i < N && x + i < N; i++)
        {
            if (table[y + i][x + i] == NO)
                break;
            if (table[y + i][x + i] == player)
                f2 = 1;
        }
    if (table[y - 1][x + 1] == enm && (h == 1 || h == 4 || h == 5 || h == 8))
        for (i = 2; y - i >= 0 && x + i < N; i++)
        {
            if (table[y - i][x + i] == NO)
                break;
            if (table[y - i][x + i] == player)
                f2 = 1;
        }
    if (table[y + 1][x - 1] == enm && (h == 1 || h == 2 || h == 3 || h == 6))
        for (i = 2; y + i < N && x - i >= 0; i++)
        {
            if (table[y + i][x - i] == NO)
                break;
            if (table[y + i][x - i] == player)
                f2 = 1;
        }
    if (f2 == 0)
        return 0;
    return 1;
}
int whereareyou(int x, int y)
{
    if ((2 <= y && y <= N - 3) && (2 <= x && x <= N - 3))
        return 1;
    else if ((0 <= y && y < 2) && (2 <= x && x <= N - 3))
        return 2;
    else if ((2 <= y && y <= N - 3) && (N - 2 <= x && x < N))
        return 3;
    else if ((N - 2 <= y && y < N) && (2 <= x && x <= N - 3))
        return 4;
    else if ((2 <= y && y <= N - 3) && (0 <= x && x < 2))
        return 5;
    else if ((0 <= y && y < 2) && (N - 2 <= x && x < N))
        return 6;
    else if ((N - 2 <= y && y < N) && (N - 2 <= x && x < N))
        return 7;
    else if ((N - 2 <= y && y < N) && (0 <= x && x < 2))
        return 8;
    else if ((0 <= y && y < 2) && (0 <= x && x < 2))
        return 9;
    else
        exit(8);
}
void set(char player, int x, int y)
{
    //�ՖʍX�V
    int i, j;
    int h = whereareyou(x, y);
    char enm = player == ME ? YOU : ME;
    if (table[y - 1][x] == enm && (h == 1 || h == 3 || h == 4 || h == 5 || h == 7 || h == 8))
        for (i = y - 2; i >= 0; i--)
        {
            if (table[i][x] == NO)
                break;
            if (table[i][x] == player)
            {
                reversi(player, x, y, x, i);
                break;
            }
        }
    if (table[y + 1][x] == enm && (h == 1 || h == 2 || h == 3 || h == 5 || h == 6 || h == 9))
        for (i = y + 2; i < N; i++)
        {
            if (table[i][x] == NO)
                break;
            if (table[i][x] == player)
            {
                reversi(player, x, y, x, i);
                break;
            }
        }
    if (table[y][x - 1] == enm && (h == 1 || h == 2 || h == 3 || h == 4 || h == 6 || h == 7))
        for (i = x - 2; i >= 0; i--)
        {
            if (table[y][i] == NO)
                break;
            if (table[y][i] == player)
            {
                reversi(player, x, y, i, y);
                break;
            }
        }
    if (table[y][x + 1] == enm && (h == 1 || h == 2 || h == 4 || h == 5 || h == 8 || h == 9))
        for (i = x + 2; i < N; i++)
        {
            if (table[y][i] == NO)
                break;
            if (table[y][i] == player)
            {
                reversi(player, x, y, i, y);
                break;
            }
        }
    if (table[y - 1][x - 1] == enm && (h == 1 || h == 3 || h == 4 || h == 7))
        for (i = 2; y - i >= 0 && x - i >= 0; i++)
        {
            if (table[y - i][x - i] == NO)
                break;
            if (table[y - i][x - i] == player)
            {
                reversi(player, x, y, x - i, y - i);
                break;
            }
        }
    if (table[y + 1][x + 1] == enm && (h == 1 || h == 2 || h == 5 || h == 9))
        for (i = 2; y + i < N && x + i < N; i++)
        {
            if (table[y + i][x + i] == NO)
                break;
            if (table[y + i][x + i] == player)
            {
                reversi(player, x, y, x + i, y + i);
                break;
            }
        }
    if (table[y - 1][x + 1] == enm && (h == 1 || h == 4 || h == 5 || h == 8))
        for (i = 2; y - i >= 0 && x + i < N; i++)
        {
            if (table[y - i][x + i] == NO)
                break;
            if (table[y - i][x + i] == player)
            {
                reversi(player, x, y, x + i, y - i);
                break;
            }
        }
    if (table[y + 1][x - 1] == enm && (h == 1 || h == 2 || h == 3 || h == 6))
        for (i = 2; y + i < N && x - i >= 0; i++)
        {
            if (table[y + i][x - i] == NO)
                break;
            if (table[y + i][x - i] == player)
            {
                reversi(player, x, y, x - i, y + i);
                break;
            }
        }
}
void reversi(char player, int x1, int y1, int x2, int y2)
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
