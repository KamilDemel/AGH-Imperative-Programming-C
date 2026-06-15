#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1024
#define BUF_SIZE  1024


int get(int cols, int row, int col, const int* A) {
    int indeks = (row * cols) + col;
    return A[indeks];

}

void set(int cols, int row, int col, int* A, int value) {
    int indeks = (row * cols) + col;
    A[indeks] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int* A, int* B, int* AB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB;j++) {
            int suma = 0;
            for (int k = 0; k < colsA; k++) {
                int element_A = get(colsA,i,k,A);
                int element_B = get(colsB,k,j,B);
                suma = suma + (element_A * element_B);
            }
        set(colsB,i,j,AB,suma);
        }
    }
}

void read_mat(int rows, int cols, int* t) {
    int value;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &value);
            set(cols,i,j,t,value);
        }
    }
}

void print_mat(int rows, int cols, int* t) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", get(cols,i,j,t));
        }
        printf("\n");
    }
}


int read_int_lines_cont(int* ptr_array[]) {
    int *tasma = ptr_array[0];
    int write_pos = 0;
    int wiersze = 0;
    char buffer[BUF_SIZE];
    while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        ptr_array[wiersze] = &tasma[write_pos];
        char *current = buffer;
        char *next_space;
        long val = strtol(current,&next_space,10);
        while (current != next_space) {
            tasma[write_pos++] = (int)val;
            current = next_space;
            val = strtol(current, &next_space, 10);
        }
        wiersze++;
    }
    ptr_array[wiersze] = &tasma[write_pos];
    return wiersze;
}

void write_int_line_cont(int *ptr_array[], int n) {
    int dlugosc = ptr_array[n+1] - ptr_array[n];
    for (int i = 0; i < dlugosc; i++) {
        int liczba = ptr_array[n][i];
        printf("%d ", liczba * liczba);
    }
    printf("\n");
}


int read_char_lines(char *array[]) {
    char buffer[BUF_SIZE];
    int wiersze = 0;
    while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        int len = strlen(buffer);
        array[wiersze] = malloc(len + 1);
        strcpy(array[wiersze], buffer);
        wiersze++;
    }
    return wiersze;
}

void write_char_line(char *array[], int n) {
    printf("%s", array[n]);
}

void delete_lines(char *array[]) {
    int i = 0;
    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
}

int read_int(void) {
    char c_buf[BUF_SIZE];
    fgets(c_buf, BUF_SIZE, stdin);
    return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
    const int to_do = read_int();

    int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
    int n, rowsA, colsA, rowsB, colsB;
    char* char_lines_array[TAB_SIZE] = { NULL };
    int continuous_array[TAB_SIZE];
    int* ptr_array[TAB_SIZE];

    switch (to_do) {
        case 1:
            scanf("%d %d", &rowsA, &colsA);
            read_mat(rowsA, colsA, A);
            scanf("%d %d", &rowsB, &colsB);
            read_mat(rowsB, colsB, B);
            prod_mat(rowsA, colsA, colsB, A, B, AB);
            print_mat(rowsA, colsB, AB);
            break;
        case 2:
            n = read_int() - 1;
            ptr_array[0] = continuous_array;
            read_int_lines_cont(ptr_array);
            write_int_line_cont(ptr_array, n);
            break;
        case 3:
            n = read_int() - 1;
            read_char_lines(char_lines_array);
            write_char_line(char_lines_array, n);
            delete_lines(char_lines_array);
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}

