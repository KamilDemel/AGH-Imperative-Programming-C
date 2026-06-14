#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 100

enum states { S0, S1 };
enum symbols { Z0, Z1 };
enum symbols memory[N];

bool step(int *position, enum states *state, const int n) {
        if (*state == S0 && memory[*position] == Z0){
            if (*position - 1 >= 0) {
                (*position)--;
            }
            else {
                *position = n - 1;
            }
            return true;
        }
        if (*state == S0 && memory[*position] == Z1){
            memory[*position] = Z0;
            *state = S1;
            if (*position + 1 < n) {
                (*position)++;
            }
            else {
                *position = 0;
            }
            return true;
        }
        if (*state == S1 && memory[*position] == Z0){
            memory[*position] = Z1;
            *state = S0;
            return true;
        }
        if (*state==S1 && memory[*position] == Z1) {
            return false;
        }
    return false;
}

int main(void) {
    unsigned int seed;
    int n, position;
    enum states state = S0;
    scanf("%u %d %d", &seed, &n, &position);
    srand(seed);
    for (int i = 0; i < n; ++i) {
        int s = rand() % 2;
        if (s == 0) memory[i] = Z0;
        else memory[i] = Z1;
    }
    int count = 0;
    while (step(&position,&state,n)) {
        count++;
    }
    printf("%d %d\n", count, position);
    return 0;
}

