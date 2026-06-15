#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

int guess_a_letter(char* text, const char* original_text) {
    int czy_trafiono = 0;
    char losowa_litera = 'A' + (rand() % 26);
    for (int j = 0; j < strlen(original_text); j++) {
        if (losowa_litera == original_text[j] && text[j] == '_') {
            text[j] = losowa_litera;
            czy_trafiono = 1;

        }
    }
    return czy_trafiono;
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player) {
    *p_player = 0;
    char* hidden_text = malloc((strlen(original_text) + 1) * sizeof(char));
    int len = strlen(original_text);
    for (int i = 0;i < len;i++) {
        if (isalpha(original_text[i])) {
            hidden_text[i] = '_';
        }
        else {
            hidden_text[i] = ' ';
        }
    }
    hidden_text[len] = '\0';
    bool czy_odgadnieto = false;

    for (int i = 0; i < turns; i++) {
        if (czy_odgadnieto) {
            break;
        }
        while (true) {
            int wynik = guess_a_letter(hidden_text, original_text);
            if (wynik == 0) {
                break;
            }
            if (strcmp(hidden_text, original_text) == 0) {
                czy_odgadnieto = true;
                break;
            }
        }
        if (!czy_odgadnieto) {
            *p_player = (*p_player + 1) % number_of_players;
        }
    }
    return hidden_text;
}

int main() {

    const char* texts[MAX_TEXTS] = {
        "DUTY AND HONOR",
        "SUPPORT AND DEFEND",
        "SHADOW OF THE DRAGON",
        "FULL FORCE AND EFFECT",
        "THE TEETH OF THE TIGER",
        "CLEAR AND PRESENT DANGER",
        "QUO VADIS",
        "ADAM MICKIEWICZ",
        "ALBERT EINSTEIN",
        "DENNIS RITCHIE",
        "FIZYKA KWANTOWA",
        "PROGRAMOWANIE IMPERATYWNE",
        "ALGORYTMY I STRUKTURY DANYCH",
        "BRIAN KERNIGHAN",
        "COMMAND AUTHORITY",
        "POINT OF CONTACT",
        "WILLIAM SHAKESPEARE",
        "THE BEAR AND THE DRAGON",
        "LINE OF DEMARCATION",
        "TARGET ACQUIRED"
    };

    int number_of_players, turns, player;
    unsigned seed;

    scanf("%d %u %d", &number_of_players, &seed, &turns);
    srand(seed);
    const int number = rand() % MAX_TEXTS;
    char* text = play(texts[number], number_of_players, turns, &player);
    printf("%s\n", text);
    printf("%d\n", player);
    free(text);

    return EXIT_SUCCESS;
}

