#include <stdio.h>
//отрисовка
void draw(const int *rocket_1_Y, const int *rocket_2_Y, const int *ball1_x, const int *ball1_y,
          int *scPlayer1, int *scPlayer2, int HEIGHT_SCRING, int WIDTH_SCRING) {
    printf("                                      %d:%d\n", *scPlayer1, *scPlayer2);

    for (int y = 0; y < HEIGHT_SCRING; y++) {
        for (int x = 0; x < WIDTH_SCRING + 1; x++) {
            if ((x == 0 && y > *rocket_1_Y - 2 && y < *rocket_1_Y + 2) ||
                (x == 80 && y > *rocket_2_Y - 2 && y < *rocket_2_Y + 2)) {
                printf("|");
            } else if (x == *ball1_x && y == *ball1_y) {
                printf("o");
            } else if (x == WIDTH_SCRING / 2) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

//отскок от стены
void otskok_w(int y, int *n) {
    if (*n == 1) {
        if (y < 1) *n = 2;
    }
    if (*n == 2) {
        if (y > 24) *n = 1;
    }
    if (*n == 3) {
        if (y < 1) *n = 4;
    }
    if (*n == 4) {
        if (y > 24) *n = 3;
    }
}
//отскок от ракетки или промах
void otskok_r(int *x, int *y, int *n, int *s1, int *s2, const int *r1, const int *r2) {
    if ((*x < 2) && (*y > *r1 - 1) && (*y < *r1 + 3)) {
        *n += 2;
    }

    if ((*x > 80) && (*y > *r2 - 1) && (*y < *r2 + 3)) {
        *n -= 2;
    }

    if ((*x < 2) && ((*y < *r1) || (*y > *r1 + 2))) {
        *s2 += 1;
        *x = 20;
        *y = 12;
        *n = 1;
    }
    if ((*x > 80) && ((*y < *r2) || (*y > *r2 + 2))) {
        *s1 += 1;
        *x = 20;
        *y = 12;
        *n = 1;
    }
}

//движение 1-ой ракетки
void rocket(int *r1, int *r2) {
    char write = getchar();
    switch (write) {
        case 'A':
        case 'a':
            if (*r1 > 0) {
                *r1 -= 1;
            }
            break;
        case 'Z':
        case 'z':
            if (*r1 < 22) {
                *r1 += 1;
            }
            break;
        case 'K':
        case 'k':
            if (*r2 > 0) {
                *r2 -= 1;
            }
            break;
        case 'M':
        case 'm':
            if (*r2 < 22) {
                *r2 += 1;
            }
            break;
        case ' ':
            break;
    }
}

//координата мяча по х
int ball_x(int x, int n) {
    switch (n) {
        case 1:
            x = x - 1;
            break;
        case 2:
            x = x - 1;
            break;
        case 3:
            x = x + 1;
            break;
        case 4:
            x = x + 1;
            break;
        default:
            printf("invalid direction\n");

            return x;
    }
    return x;
}
//координата мяча по у
int ball_y(int y, int n) {
    switch (n) {
        case 1:
            y = y - 1;
            break;
        case 2:
            y = y + 1;
            break;
        case 3:
            y = y - 1;
            break;
        case 4:
            y = y + 1;
            break;

        default:
            printf("invalid direction\n");

            return y;
    }
    return y;
}

//счет игры по правилам
int score(int s1, int s2, char name1, char name2) {
    if (s1 == 21) {
        printf("%c win", name1);
        printf("Game finished");
        return 1;
    }
    if (s2 == 21) {
        printf("%c win", name2);
        printf("Game finished");
        return 1;
    }
    return 0;
}

int main() {
    int x = 20, y = 12, s1 = 0, s2 = 0, n = 1, r1 = 12, r2 = 12;
    int height = 25, width = 80;
    char name1, name2;
    printf("Name of the left player(one letter):");
    scanf("%c/n", &name1);
    printf("Name of the right player(one letter):");
    scanf("%c/n", &name2);
    draw(&r1, &r2, &x, &y, &s1, &s2, height, width);
    while (1) {
        x = ball_x(x, n);
        y = ball_y(y, n);
        rocket(&r1, &r2);
        otskok_w(y, &n);
        otskok_r(&x, &y, &n, &s1, &s2, &r1, &r2);
        draw(&r1, &r2, &x, &y, &s1, &s2, height, width);
        if (score(s1, s2, name1, name2) == 1) {
            return 0;
        }
    }
}
