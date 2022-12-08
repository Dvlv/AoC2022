#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 99
#define COLS 99

int trees[COLS][ROWS];
int visible_trees = 0;

int can_tree_be_seen(int row, int col) {
    int tree_height = trees[col][row];
    printf("tree (%d,%d) @ %d\n", col, row, tree_height);

    if (col == 0 || col == COLS-1) {
        printf("   visible - l/r edge\n");
        return 1; // l/r edge
    }
    if (row == 0 || row == ROWS-1) {
        printf("   visible - t/b edge\n");
        return 1; // t/b edge
    }


    // left
    int can_be_seen_left = 1;
    for (int i = col-1; i >= 0; i--) {
        int other_tree = trees[i][row];
        if (other_tree >= tree_height) {
            printf("  not visible left due to %d", other_tree);
            can_be_seen_left = 0;
        }
    }

    // right
    int can_be_seen_right = 1;
    for (int j = col+1; j < COLS ; j++) {
        int other_tree = trees[j][row];
        if (other_tree >= tree_height) {
            can_be_seen_right = 0;
        }
    }

    // above
    int can_be_seen_above = 1;
    for (int k = row-1; k >= 0; k--) {
        int other_tree = trees[col][k];
        if (other_tree >= tree_height) {
            can_be_seen_above = 0;
        }
    }

    // below
    int can_be_seen_below = 1;
    for (int l = row+1; l < ROWS; l++) {
        int other_tree = trees[col][l];
        if (other_tree >= tree_height) {
            can_be_seen_below = 0;
        }
    }

    int can_be_seen_at_all = 0;
    if (can_be_seen_above || can_be_seen_below || can_be_seen_left || can_be_seen_right) {
        printf("  visible - seen side \n");
        can_be_seen_at_all = 1;
    }

    return can_be_seen_at_all;

}

int main() {

    FILE *f = fopen("input8.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 100;


    int r_idx = 0;
    while((getline(&current_line, &n, f)) > 0) {
        for (int i = 0; i < COLS; i++) {
            char tree = current_line[i];
            int itree = atoi(&tree);
            trees[i][r_idx] = itree;
        }
        r_idx++;
    }

    fclose(f);

    int total_seen = 0;
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (can_tree_be_seen(r, c)) {
                total_seen++;
                printf("total seen %d\n", total_seen);
            }
        }
    }
    

    printf("total seen: %d\n", total_seen);
}