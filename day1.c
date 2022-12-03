#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ELVES 500

void set_most_cals(int new_val, int* most, int* second, int* third) {
    if (new_val >= *most) {
        *third = *second;
        *second = *most;
        *most = new_val;
    } else if (new_val >= *second) {
        *third = *second;
        *second = new_val;
    } else if (new_val > *third) {
        *third = new_val;
    }
}

int main() {
    FILE *f = fopen("input1.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 255;
    int elf_cals[NUM_ELVES] = {0};
    int idx = 0;

    int elf_most_cals = 0;
    int elf_second_most = 0;
    int elf_third_most = 0;

    while ((getline(&current_line, &n, f)) > 0) {
        if (strcmp(current_line, "\n") == 0) {
            set_most_cals(elf_cals[idx], &elf_most_cals, &elf_second_most, &elf_third_most);
            idx++;
        } else {
            elf_cals[idx] += atoi(current_line);
        }
    }

    fclose(f);

    // for(int i = 0; i < NUM_ELVES; i++) {
    //     if (elf_cals[i] > 0) {
    //         printf("Elf %d has %d cals\n", i+1, elf_cals[i]);
    //     }
    // }
    printf("Elf with most cals has %d\n", elf_most_cals);
    printf("Elf with second most cals has %d\n", elf_second_most);
    printf("Elf with third most cals has %d\n", elf_third_most);

    printf("Total top 3 = %d\n", elf_most_cals+elf_second_most+elf_third_most);

}