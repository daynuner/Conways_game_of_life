#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define W 339
#define H 168

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void ansi(void) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m;
    SetConsoleOutputCP(CP_UTF8);
    if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

int main() {
    int i, j, x, y, n, g[H][W], next[H][W];
    srand((unsigned)time(NULL));
    ansi();

    for (i = 0; i < H * W; i++) g[i / W][i % W] = rand() % 5 == 0;

    printf("\033[?25l");
    while (1) {
        printf("\033[H");
        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) {
                n = 0;
                for (y = -1; y <= 1; y++)
                    for (x = -1; x <= 1; x++)
                        if (x || y) n += g[(i + y + H) % H][(j + x + W) % W] > 0;

                if (g[i][j] > 0) next[i][j] = (n == 2 || n == 3) ? g[i][j] + 1 : 0;
                else next[i][j] = (n == 3) ? 1 : 0;

                if (g[i][j]) printf("\033[38;5;%dm█", g[i][j] > 10 ? 196 : 46 + g[i][j] * 10);
                else printf(" ");
            }
            puts("");
        }
        for (i = 0; i < H * W; i++) g[i / W][i % W] = next[i / W][i % W];
        Sleep(30);
    }
}
