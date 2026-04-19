#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define W 30
#define H 25

int main(void) {
    int g[H][W] = {0};
    int next[H][W] = {0};
    int i, j, x, y, n;

    srand((unsigned)time(NULL));

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            g[i][j] = (rand() % 5 == 0);
        }
    }

    printf("\033[?25l");
    printf("\033[2J");

    while (1) {
        printf("\033[H");

        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) {
                n = 0;
                for (y = -1; y <= 1; y++) {
                    for (x = -1; x <= 1; x++) {
                        if (x || y) {
                            int ii = (i + y + H) % H;
                            int jj = (j + x + W) % W;
                            n += g[ii][jj] > 0;
                        }
                    }
                }

                if (g[i][j] > 0) next[i][j] = (n == 2 || n == 3) ? g[i][j] + 1 : 0;
                else next[i][j] = (n == 3) ? 1 : 0;

                if (g[i][j] > 0) {
                    int color = (g[i][j] > 10) ? 196 : 46 + g[i][j] * 10;
                    if (color > 255) color = 255;
                    printf("\033[38;5;%dm█", color);
                } else {
                    putchar(' ');
                }
            }
            putchar('\n');
            
        }

        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) {
                g[i][j] = next[i][j];
            }
        }
        usleep(60000);
    }

    return 0;
}
