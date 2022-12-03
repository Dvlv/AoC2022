
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_dupe(char* first_half, char* second_half, int log) {
    char dupe;
    for (int i = 0; i < strlen(first_half); i++) {
        char c = first_half[i];
        if (c == '\n') continue;
        if (log) {
            printf("Trying %c in str %s", c, second_half);
        }

        if (strchr(second_half, c) != NULL) {
            dupe = c;
        }
    }

    if (!dupe) {
        printf("Could not find dupe!\n");
    }

    return dupe;
}

char find_tri_dupe(char* first_bp, char* second_bp, char* third_bp, int log) {
    char dupe;
    for (int i = 0; i < strlen(first_bp); i++) {
        char c = first_bp[i];
        if (c == '\n') continue;
        if (log) {
            printf("Trying %c in str %s", c, second_bp);
        }

        if (strchr(second_bp, c) != NULL && strchr(third_bp, c) != NULL) {
            dupe = c;
        }
    }

    if (!dupe) {
        printf("Could not find dupe!\n");
    }

    return dupe;
}

int get_prio(char c) {
    // A = 65
    // Z = 90
    // a = 97
    // z = 122
    if (c > 64 && c < 91) {
        return c - 38;
    }
    if (c > 96 && c < 123) {
        return c - 96;
    }

    printf("Err: Trying to get val of %c\n", c);
    exit(1);
}

int part1_main() {

    FILE *f = fopen("input3.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 255;

    int score = 0;

    int line = 1;

    while ((getline(&current_line, &n, f)) > 0) {
        int num_items = strlen(current_line);
        int first_half_len = (num_items)/2;

        char *first_half = malloc(first_half_len + 1);
        memcpy(first_half, current_line, first_half_len);
        first_half[first_half_len] = '\0';

        char *second_half = &current_line[num_items-1 - first_half_len];

        int log = line == 30 ? 1 : 0;
        char dupe = find_dupe(first_half, second_half, log);
        if (log) {
            printf("First half len = %d\n", first_half_len);
        }

        printf("%d Dupe found: %c", line, dupe);

        int prio = get_prio(dupe);
        printf("; Dupe val %d\n", prio);
        score += prio;
        line++;
    }

    fclose(f);

    printf("Score: %d\n", score);
}

int main() {

    FILE *f = fopen("input3.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *elf1_backpack;
    char *elf2_backpack;
    char *elf3_backpack;
    size_t n = 255;

    int score = 0;

    int line = 1;

    while ((getline(&elf1_backpack, &n, f)) > 0) {
        getline(&elf2_backpack, &n, f);
        getline(&elf3_backpack, &n, f);

        char dupe = find_tri_dupe(elf1_backpack, elf2_backpack, elf3_backpack, 0);

        printf("Found dupe %c", dupe);

        int prio = get_prio(dupe);
        printf("; Dupe val %d\n", prio);
        score += prio;
        line++;
    }

    fclose(f);

    printf("Score: %d\n", score);
}