#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

void find_comments(int*, int*);
int find_idents(void);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {
    "auto", "break", "case", "char",
    "const", "continue", "default", "do",
    "double", "else", "enum", "extern",
    "float", "for", "goto", "if",
    "int", "long", "register", "return",
    "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

void find_comments(int *line_comment_counter, int *block_comment_counter) {
    *line_comment_counter = 0;
    *block_comment_counter = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            int next = getchar();
            if (next == '/') {
                (*line_comment_counter)++;
                int inner_c;
                while ((inner_c = getchar()) != '\n' && inner_c != EOF) {
                }
            }
            else if (next == '*') {
                (*block_comment_counter)++;
                int inner_c;
                while ((inner_c = getchar()) != EOF) {
                    if (inner_c == '*') {
                        int possible_slash = getchar();
                        if (possible_slash == '/') {
                            break;
                        }
                        ungetc(possible_slash,stdin);
                    }
                }
            }
            else {
                ungetc(next,stdin);
            }
            }
        }
}

int find_idents(void) {
    int licznik_unikalnych = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '/') {
            int next = getchar();
            if (next == '/') {
                int inner_c;
                while ((inner_c = getchar()) != '\n' && inner_c != EOF) {
                }
            }
            else if (next == '*') {
                int inner_c;
                while ((inner_c = getchar()) != EOF) {
                    if (inner_c == '*') {
                        int possible_slash = getchar();
                        if (possible_slash == '/') {
                            break;
                        }
                        ungetc(possible_slash,stdin);
                    }
                }
            }
            else {
                ungetc(next,stdin);
            }
        }
        else if (c == '"') {
            while (getchar() != '"') {

            }
        }
        else if (c == '\'') {
            while (getchar() != '\'') {

            }
        }
        else if (isalpha(c) || c == '_') {
            int inner_c;
            char napis[100];
            int i = 0;
            napis[i++] = (char)c;
            while ((inner_c = getchar()) == '_' || isalnum(inner_c)) {
                napis[i++] = (char)inner_c;
            }
            napis[i] = '\0';
            ungetc(inner_c, stdin);
            bool is_uniklane = true;
            for (int j = 0; j < licznik_unikalnych;j++) {
                if (strcmp(identifiers[j],napis) == 0) {
                    is_uniklane = false;
                    break;
                }
            }
            bool czy_dodac = is_uniklane;
            if (is_uniklane) {
                for (int z =0; z < 32;z++){
                    if (strcmp(keywords[z],napis) == 0) {
                        czy_dodac = false;
                        break;
                    }
                }
            }
            if (czy_dodac) {
                strcpy(identifiers[licznik_unikalnych], napis);
                licznik_unikalnych++;
            }
        }
    }
    return licznik_unikalnych;
}

int read_int() {
    char line[MAX_LINE];
    fgets(line, MAX_LINE, stdin);
    return (int)strtol(line, NULL, 10);
}

int main(void) {
    int line_comment_counter, block_comment_counter;
    const int to_do = read_int();
    switch (to_do) {
        case 1:
            find_comments(&line_comment_counter, &block_comment_counter);
            printf("%d %d\n", block_comment_counter, line_comment_counter);
            break;
        case 2:
            printf("%d\n", find_idents());
            break;
        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }
    return 0;
}

