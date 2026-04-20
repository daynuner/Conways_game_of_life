#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W 40
#define H 25

int main() {
    int i, j, x, y, n, g[H][W], next[H][W];
    // Рандомное заполнение
    for (i = 0; i < H * W; i++) g[i / W][i % W] = rand() % 5 == 0;

    printf("\033[?25l"); // Скрыть курсор
    while (1) {
        printf("\033[H"); // В начало экрана
        for (i = 0; i < H; i++) {
            for (j = 0; j < W; j++) {
                n = 0;
                // Считаем соседей
                for (y = -1; y <= 1; y++)
                    for (x = -1; x <= 1; x++)
                        if (x || y) n += g[(i + y + H) % H][(j + x + W) % W] > 0;

                // Правила жизни и инкремент цвета (возраста)
                if (g[i][j] > 0) next[i][j] = (n == 2 || n == 3) ? g[i][j] + 1 : 0;
                else next[i][j] = (n == 3) ? 1 : 0;

                // Вывод: цвет меняется от значения в массиве (g[i][j])
                if (g[i][j]) printf("\033[38;5;%dm█", g[i][j] > 10 ? 196 : 46 + g[i][j] * 10);
                else printf(" ");
            }
            puts("");
        }
        for (i = 0; i < H * W; i++) g[i / W][i % W] = next[i / W][i % W];
        usleep(30000); 
    }
}
