#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 8

typedef unsigned long long int ulli;

void show(void);
void showUlli(ulli);      // ulliを表示
ulli isFinished(void);    // 盤面に空きコマの数
void reversi(int);        // tukure
int whoIsTheWinner(void); // 勝敗判定
ulli howManyBits(ulli);   // pb, ob, ebの数を返す
void put(int, int, int);  // 本当に要るのかな
ulli getLegalHands(int);  // selが指す奴にとっての合法手を返す 0: pb, 1: ob

ulli pb = 0x0000000810000000, ob = 0x0000001008000000;
char boardStates[3] = {'O', 'X', '-'};

int main()
{
    int turn = 0;
    showUlli(getLegalHands(0));
    // printf("(row, column) => ");
    // scanf("%d%d", &r, &c);

    // 盤面全埋まりなら終わる
    // while (isFinished())
    // {
    //     // 盤面見せて
    //     show();
    //     // 置けるか確かめて置けるなら, 置かせて確かめて大丈夫なら返す
    //     reversi(turn);
    // }
    // switch (whoIsTheWinner())
    // {
    // case 2:
    //     printf("I am a winner!\n");
    //     break;
    // case 1:
    //     printf("I am a loser...\n");
    //     break;
    // default:
    //     printf("I am not neither.\n");
    //     break;
    // }
    return 0;
}
/*
8*8のテーブルを64bit変数で管理する。よって用いる型はlong long int(8byte = 64bit)で、プレイヤー分二つのlong long int変数が最低限必要となる。
64bitのため16進数で表すとなると2^4だから64/4 = 16桁で表せられる。
%llxでいい感じにフォーマット指定できる。バイナリでは出してくれないけど16進数で出力してくれる。
long long intは負数も含んでて、負数のシフトのとき空きbitに1が入るからunsignedにしといた。
石の位置はのは y xで貰って tmp = 0x8000000000000000;をtmp >>= ((y*N)+x)でいける！
init()ほしいかも。
*/
void reversi(int turn)
{
    int whoseTurn = turn % 2;
    ulli okHands = 0x0000000000000000;
    // 合法手求める
    // 座標入れさせる
    // 合法手とのandが0じゃなかったらok これがcanPutに等しい
    // 返す
    int r, c;

    if (turn % 2 == 0)
    {
        scanf("%d %d", &r, &c);
    }
}
ulli getLegalHands(int sel)
{
    ulli o, o2, p, tmp = 0x0000000000000000, emptyBoard = ~(pb | ob), legalBoard = 0x0000000000000000, horizontalMask = 0x7E7E7E7E7E7E7E7E, verticalMask = 0x00ffffffffffff00, allSideMask = 0x007e7e7e7e7e7e00;
    if (sel == 0)
    {
        o2 = o = ob;
        p = pb;
    }
    else if (sel == 1)
    {
        o2 = o = pb;
        p = ob;
    }
    else
    {
        exit(0);
    }

    return legalBoard;
}
void put(int r, int c, int sel)
{
    int n = N * N - N * r - c - 1;
    switch (sel)
    {
    case 0:
        pb |= (1 << n);
        break;
    case 1:
        ob |= (1 << n);
        break;
    default:
        break;
    }
}
void show(void)
{
    int i, j, sel;
    system("cls");
    printf("ME: O, CPU: X\n");
    printf("  ");
    for (i = 0; i < N; i++)
        printf("%d ", i);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (j == 0)
                printf("%d ", i);
            if ((pb >> (N * N - N * i - j - 1)) & 1)
                sel = 0;
            else if ((ob >> (N * N - N * i - j - 1)) & 1)
                sel = 1;
            else
                sel = 2;
            printf("%c ", boardStates[sel]);
        }
        printf("\n");
    }
}
void showUlli(ulli table)
{
    printf("showUlli\n");
    int i, j;
    system("cls");
    printf("  ");
    for (i = 0; i < N; i++)
        printf("%d ", i);
    printf("\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (j == 0)
                printf("%d ", i);
            printf("%d ", (table >> (N * N - N * i - j - 1)) & 1);
        }
        printf("\n");
    }
}
ulli isFinished(void)
{
    return N * N - howManyBits(pb | ob);
}
int whoIsTheWinner(void)
{
    ulli p, o;
    p = howManyBits(pb);
    o = howManyBits(ob);
    if (p > o)
        return 2;
    else if (p < o)
        return 1;
    else
        return 0;
}
ulli howManyBits(ulli v)
{
    v = (v & 0x5555555555555555) + (v >> 1 & 0x5555555555555555);
    v = (v & 0x3333333333333333) + (v >> 2 & 0x3333333333333333);
    v = (v & 0x0f0f0f0f0f0f0f0f) + (v >> 4 & 0x0f0f0f0f0f0f0f0f);
    v = (v & 0x00ff00ff00ff00ff) + (v >> 8 & 0x00ff00ff00ff00ff);
    v = (v & 0x0000ffff0000ffff) + (v >> 16 & 0x0000ffff0000ffff);
    v = (v & 0x00000000ffffffff) + (v >> 32 & 0x00000000ffffffff);
    return v;
}

/*
オセロ処理: https://qiita.com/watergreat31/items/09f114799319c7ba19dc
ビット操作: https://qiita.com/qiita_kuru/items/3a6ab432ffb6ae506758
https://qiita.com/torajiro1220/items/e891355327a368a5f189
*/