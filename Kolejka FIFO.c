#include <stdio.h>


enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };


#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) {
    int status = OK;
    for (int i = 0; i < in_nr; i++) {
        curr_nr++;
        if (in < 10) {
            queue[in] = curr_nr;
            in++;
        }
        else {
            status = OVERFLOW;
        }
    }
    return status;
}

int queue_pop(int out_nr) {
    if (out_nr > in) {
        in = 0;
        return UNDERFLOW;
    }
    for (int i = 0; i < in - out_nr; i++) {
        queue[i] = queue[i+out_nr];
    }
    in = in - out_nr;
    return in;
}

int queue_state(void) {
    return in;
}

void queue_print(void) {
    for (int i = 0; i < in; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main(void) {
    int n, answer;
    do {
        scanf("%d", &n);
        if (n > 0) {
            if ((answer = queue_push(n)) < 0) printf("%d ", answer);
        } else if (n < 0) {
            if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
        } else {
            printf("\n%d\n", queue_state());
            queue_print();
        }
    } while(n != 0);

    return 0;
}

