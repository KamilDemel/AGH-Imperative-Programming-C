#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFER_SIZE 128


int czy_to_liczba(char* slowo) {
    if (isdigit(slowo[0])) {
        return 1;
    }
    if (slowo[0] == '-' && isdigit(slowo[1])) {
        return 1;
    }
    return 0;
}

int get_priority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}


typedef struct {
    char items[BUFFER_SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push(Stack *s, char op) {
    s->top = s->top + 1;
    s->items[s->top] = op;
}

char pop(Stack *s) {
    if (is_empty(s) == 1) {
        return '\0';
    }
    char sciagniety_znak = s->items[s->top];
    s->top = s->top - 1;
    return sciagniety_znak;
}

char peek(Stack *s) {
    if (is_empty(s) == 1) {
        return '\0';
    }
    return s->items[s->top];
}


typedef struct {
    int items[BUFFER_SIZE];
    int top;
} IntStack;

void init_int_stack(IntStack *s) {
    s->top = -1;
}

int is_int_empty(IntStack *s) {
    if (s->top == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push_int(IntStack *s, int value) {
    s->top = s->top + 1;
    s->items[s->top] = value;
}

int pop_int(IntStack *s) {
    if (is_int_empty(s) == 1) {
        return 0;
    }
    int sciagnieta_liczba = s->items[s->top];
    s->top = s->top - 1;
    return sciagnieta_liczba;
}

void to_onp(char* expression, char* onp) {
    Stack moj_stos;
    init_stack(&moj_stos);
    const char delimits[] = " \n\t";
    onp[0] = '\0';

    char *token = strtok(expression, delimits);

    while (token != NULL) {

        if (czy_to_liczba(token) == 1) {
            strcat(onp, token);
            strcat(onp, " ");
        }
        else {
            char obecny_operator = token[0];

            if (obecny_operator == '(') {
                push(&moj_stos, obecny_operator);
            }
            else if (obecny_operator == ')') {
                while (1) {
                    char sciagniety_znak = pop(&moj_stos);

                    if (sciagniety_znak == '(') {
                        break;
                    }

                    char jako_napis[2];
                    jako_napis[0] = sciagniety_znak;
                    jako_napis[1] = '\0';

                    strcat(onp, jako_napis);
                    strcat(onp, " ");
                }
            }
            else {
                while (is_empty(&moj_stos) == 0) {

                    char znak_pod_spodem = peek(&moj_stos);
                    int priorytet_stosu = get_priority(znak_pod_spodem);
                    int moj_priorytet = get_priority(obecny_operator);

                    if (priorytet_stosu >= moj_priorytet) {
                        char do_wyrzucenia = pop(&moj_stos);

                        char jako_napis[2];
                        jako_napis[0] = do_wyrzucenia;
                        jako_napis[1] = '\0';

                        strcat(onp, jako_napis);
                        strcat(onp, " ");
                    }
                    else {
                        break;
                    }
                }
                push(&moj_stos, obecny_operator);
            }
        }
        token = strtok(NULL, delimits);
    }

    while (is_empty(&moj_stos) == 0) {
        char ostatni_znak = pop(&moj_stos);

        char jako_napis[2];
        jako_napis[0] = ostatni_znak;
        jako_napis[1] = '\0';

        strcat(onp, jako_napis);
        strcat(onp, " ");
    }
}

int evaluate_onp(char* onp) {
    IntStack stos_liczb;
    init_int_stack(&stos_liczb);

    char onp_copy[BUFFER_SIZE];
    strcpy(onp_copy, onp);

    char *token = strtok(onp_copy, " \n\t");

    while (token != NULL) {

        if (czy_to_liczba(token) == 1) {
            int wartosc_liczbowa = atoi(token);
            push_int(&stos_liczb, wartosc_liczbowa);
        }
        else {
            char dzialanie = token[0];

            int prawa_strona = pop_int(&stos_liczb);
            int lewa_strona = pop_int(&stos_liczb);

            int wynik_dzialania = 0;

            if (dzialanie == '+') {
                wynik_dzialania = lewa_strona + prawa_strona;
            }
            else if (dzialanie == '-') {
                wynik_dzialania = lewa_strona - prawa_strona;
            }
            else if (dzialanie == '*') {
                wynik_dzialania = lewa_strona * prawa_strona;
            }
            else if (dzialanie == '/') {
                wynik_dzialania = lewa_strona / prawa_strona;
            }

            push_int(&stos_liczb, wynik_dzialania);
        }

        token = strtok(NULL, " \n\t");
    }

    int ostateczny_wynik = pop_int(&stos_liczb);
    return ostateczny_wynik;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char onp[BUFFER_SIZE] = { '\0' };

    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        to_onp(buffer, onp);

        printf("%s\n", onp);
        printf("%d\n", evaluate_onp(onp));
    }

    return 0;
}