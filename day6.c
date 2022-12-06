#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_dupe_part1(char chars_to_check[]) {
    //printf("checking %s\n", chars_to_check);
    char seenchars[5] = "    ";
    int dupe = 0;

    for (int i = 0; i < 4; i++) {
        if (strchr(seenchars, chars_to_check[i])) {
            return 1;
        } else {
            seenchars[i] = chars_to_check[i];
        }
    }
    seenchars[4] = '\0';

    return 0;
}

int has_dupe(char chars_to_check[]) {
    //printf("checking %s\n", chars_to_check);
    char seenchars[15] = "    ";
    int dupe = 0;

    for (int i = 0; i < 14; i++) {
        if (strchr(seenchars, chars_to_check[i])) {
            return 1;
        } else {
            seenchars[i] = chars_to_check[i];
        }
    }
    seenchars[14] = '\0';

    return 0;
}

int main() {

    FILE *f = fopen("input6.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 1024;

    int chars_processed = 14;

    getline(&current_line, &n, f);
    fclose(f);

    char chars_to_check[15];
    chars_to_check[15] = '\0';
    int iidx = 0;
        for (int j = 14; j > 0; j--) {
            chars_to_check[iidx] = current_line[chars_processed-j];
            iidx++;
        }

    int keep_going = has_dupe(chars_to_check);

    while (keep_going) {
        chars_processed++;
        int idx = 0;
        for (int j = 14; j > 0; j--) {
            chars_to_check[idx] = current_line[chars_processed-j];
            idx++;
        }
        keep_going = has_dupe(chars_to_check);
    }

    printf("%d chars processed\n", chars_processed);

}