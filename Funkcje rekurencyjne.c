#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 20

bool place_queens(int* queens, const int n, const int k, const int ndx) {
    static int found_count = 0;
    if (ndx == n) {
        found_count++;
        if (found_count == k) {
            return true;
        }
        return false;
    }
    for (int col = 0; col < n; col++) {
        bool safe = true;
        for (int i = 0; i < ndx;i++) {
            if (queens[i] == col || abs(queens[i] - col) == abs(i - ndx)) {
                safe = false;
                break;
            }
        }
        if (safe) {
            queens[ndx] = col;
            if (place_queens(queens,n,k,ndx+1)) {
                return true;
            }
        }
    }
    return false;
}

void print_board(const int* queens, const int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ",queens[i]);
    }
    printf("\n");
}

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int queens[N] = { 0 };
    if (place_queens(queens, n, k, 0)) {
        print_board(queens, n);
    } else {
        printf("-1\n");
    }

    return EXIT_SUCCESS;
}

