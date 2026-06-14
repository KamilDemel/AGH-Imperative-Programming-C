#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pi, pj;
    int direction;
} Ant;
int di[] = {-1, 0, 1, 0};
int dj[] = {0, 1, 0, -1};

void print_board(int** board, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void print_ant(const Ant ant) {
    int kierunek = ant.direction;
    if (kierunek == 0) {
        printf("%d %d %c\n", ant.pi, ant.pj, 'N' );
    }
    else if (kierunek == 1) {
        printf("%d %d %c\n", ant.pi, ant.pj, 'E' );
    }
    else if (kierunek == 2) {
        printf("%d %d %c\n", ant.pi, ant.pj, 'S' );
    }
    else {
        printf("%d %d %c\n", ant.pi, ant.pj, 'W' );
    }

}

void init_board(int*** board, const int n) {
    *board = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        (*board)[i] = malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            (*board)[i][j] = (rand() % 8) + 1;
        }
    }
}

void free_board(int** board, const int n) {
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

void ant_move(int** board, const int n, Ant* ant) {
    int curr_state = board[ant->pi][ant->pj];
    int move_dir_przod = ant->direction;
    int move_dir_prawo = (ant->direction + 1) % 4;
    int move_dir_dol = (ant->direction + 2) % 4;
    int move_dir_lewo = (ant->direction + 3) % 4;
    switch (curr_state) {
        case 1:
            board[ant->pi][ant->pj] = 7;
            ant->pi = ant->pi + di[move_dir_przod];
            ant->pj = ant->pj + dj[move_dir_przod];
            ant->pi = (ant->pi + n) % n;
            ant->pj = (ant->pj + n) % n;
            break;
        case 2:
            board[ant->pi][ant->pj] = 4;
            ant->direction = (ant->direction + 1) % 4;
            break;
        case 3:
            board[ant->pi][ant->pj] = 2;
            ant->direction = (ant->direction + 3) % 4;
            break;
        case 4:
            board[ant->pi][ant->pj] = 6;
            ant->pi = ant->pi + di[move_dir_prawo];
            ant->pj = ant->pj + dj[move_dir_prawo];
            ant->pi = (ant->pi + n) % n;
            ant->pj = (ant->pj + n) % n;
            break;
        case 5:
            board[ant->pi][ant->pj] = 3;
            ant->pi = ant->pi + di[move_dir_lewo];
            ant->pj = ant->pj + dj[move_dir_lewo];
            ant->pi = (ant->pi + n) % n;
            ant->pj = (ant->pj + n) % n;
            break;
        case 6:
            board[ant->pi][ant->pj] = 5;
            ant->pi = ant->pi + di[move_dir_dol];
            ant->pj = ant->pj + dj[move_dir_dol];
            ant->pi = (ant->pi + n) % n;
            ant->pj = (ant->pj + n) % n;
            break;
        case 7:
            board[ant->pi][ant->pj] = 8;
            ant->direction = (ant->direction + 2) % 4;
            break;
        case 8:
            board[ant->pi][ant->pj] = 1;
            break;

        default:
            break;
    }
}

void ant_simulation(int** board, const int n, Ant* ant, const int steps) {
    ant->pi = 0;
    ant->pj = 0;
    ant->direction = 1;
    for (int i = 0; i < steps;i++) {
        ant_move(board,n,ant);
    }
}

int main(void) {
    int** board;
    int n, steps;
    unsigned seed;
    Ant ant;
    scanf("%d %u %d", &n, &seed, &steps);
    srand(seed);
    init_board(&board, n);
    ant_simulation(board, n, &ant, steps);
    print_board(board, n);
    print_ant(ant);

    free_board(board, n);

    return 0;
}

