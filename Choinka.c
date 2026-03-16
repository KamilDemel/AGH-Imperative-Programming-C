#include <stdio.h>
int main(void) {
    int height;
    scanf("%d",&height);
    int height2;
    scanf("%d",&height2);
    for (int i = 0; i < height; i++) {
        for (int k = height; k > i+1; k--) {
            printf(" ");
        }
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }
    for (int i = 0; i < height2; i++) {
        for (int k = height; k > i+1; k--) {
            printf(" ");
        }
        for (int j = 0; j <= 2 * i; j++) {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}