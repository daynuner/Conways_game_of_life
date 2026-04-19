#include <stdio.h>

#define W 40
#define H 20

int main(void) {
    int g[H][W] = {0};
    int next[H][W] = {0};
    int i, j, x, y, n;

    g[10][10] = 1;
    g[10][11] = 1;
    g[10][12] = 1;

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            n = 0;
            for (y = -1; y <= 1; y++) {
                for (x = -1; x <= 1; x++) {
                    if (x || y) {
                        int ii = (i + y + H) % H;
                        int jj = (j + x + W) % W;
                        n += g[ii][jj];
                    }
                }
            }

            if (g[i][j]) next[i][j] = (n == 2 || n == 3);
            else next[i][j] = (n == 3);
        }
    }

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            putchar(next[i][j] ? '#' : ' ');
        }
        putchar('\n');
    }

    return 0;
}
