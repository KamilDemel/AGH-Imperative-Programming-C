#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef enum {EMPTY = 0, PLAYER1, PLAYER2} states;
int cnt[2];

void start(states board[][N], const int n) {
    for (int i = 0; i < n;i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = EMPTY;
        }
    }
    for (int i = 0; i < 4;i++) {
        for (int j = 0; j < n; j+=2) {
            if (i % 2 == 0) {
                board[i][j] = PLAYER1;
            }
            else {
                board[i][j+1] = PLAYER1;
            }
        }
    }
    for (int i = n - 1; i > n - 1 - 4; i--) {
        for (int j = 0; j < n; j+=2) {
            if (i % 2 == 0) {
                board[i][j] = PLAYER2;
            }
            else {
                board[i][j+1] = PLAYER2;
            }
        }
    }
}

int move(states board[][N], const int i, const int j, const int n) {
    if (board[i][j] == PLAYER1) {
        if (i + 1 < n && j + 1 < n && board[i+1][j+1] == EMPTY) {
            board[i][j] = EMPTY;
            board[i+1][j+1] = PLAYER1;
            return 1;
        }
        else if (i + 1 < n && j - 1 >= 0 && board[i+1][j-1] == EMPTY) {
            board[i][j] = EMPTY;
            board[i+1][j-1] = PLAYER1;
            return 1;
        }
    }
    else if (board[i][j] == PLAYER2) {
        if (i - 1 >= 0 && j + 1 < n && board[i-1][j+1] == EMPTY) {
            board[i][j] = EMPTY;
            board[i-1][j+1] = PLAYER2;
            return 1;
        }
        else if (i - 1 >= 0 && j - 1 >= 0 && board[i-1][j-1] == EMPTY) {
            board[i][j] = EMPTY;
            board[i-1][j-1] = PLAYER2;
            return 1;
        }
    }
    return 0;
}

int capture(states board[][N], const int i, const int j, const int n) {
    if (board[i][j] == PLAYER1) {
        if (i + 2 < n && j + 2 < n && board[i+1][j+1] == PLAYER2 && board[i+2][j+2] == EMPTY) {
            board[i][j] = EMPTY;
            board[i+1][j+1] = EMPTY;
            board[i+2][j+2] = PLAYER1;
            return 1;
        }
        else if (i + 2 < n && j - 2 >= 0 && board[i+1][j-1] == PLAYER2 && board[i+2][j-2] == EMPTY) {
            board[i][j] = EMPTY;
            board[i+1][j-1] = EMPTY;
            board[i+2][j-2] = PLAYER1;
            return 1;
        }
    }
    else if (board[i][j] == PLAYER2) {
        if (i - 2 >= 0 && j + 2 < n && board[i-1][j+1] == PLAYER1 && board[i-2][j+2] == EMPTY) {
            board[i][j] = EMPTY;
            board[i-1][j+1] = EMPTY;
            board[i-2][j+2] = PLAYER2;
            return 1;
        }
        else if (i - 2 >= 0 && j - 2 >= 0 && board[i-1][j-1] == PLAYER1 && board[i-2][j-2] == EMPTY) {
            board[i][j] = EMPTY;
            board[i-1][j-1] = EMPTY;
            board[i-2][j-2] = PLAYER2;
            return 1;
        }
    }
    return 0;
}

void step(states board[][N], const int n, const states player) {
    int i,j;
    do {
        i = rand() % n;
        j = rand() % n;
    } while (board[i][j] != player);
    if (player == PLAYER1) {
        if (capture(board,i,j,n) == 1){
            cnt[PLAYER2 - 1]--;
        }
        else if (move(board,i,j,n) == 1){
        }
    }
    else if (player == PLAYER2) {
        if (capture(board,i,j,n) == 1){
            cnt[PLAYER1 - 1]--;
        }
        else if (move(board,i,j,n) == 1){
        }
    }
}

int main(void) {
    states board[N][N];
    int n, steps;
    unsigned seed;

    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    cnt[0] = cnt[1] = 2 * n;
    start(board, n);
    for (int i = 0; i < steps; i++) {
        const states player = (i % 2 == 0) ? PLAYER1 : PLAYER2;
        if (cnt[player - 1] == 0) {
            break;
        }
        step(board, n, player);
    }
    printf("%d %d\n", cnt[0], cnt[1]);

    return 0;
}
