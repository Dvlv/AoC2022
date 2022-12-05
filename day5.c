#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C1_IDX 1
#define C2_IDX 5
#define C3_IDX 9
#define C4_IDX 13
#define C5_IDX 17
#define C6_IDX 21
#define C7_IDX 25
#define C8_IDX 29
#define C9_IDX 33

#define MAX_STACK_HEIGHT 50

// hardcode num of crates
char crates[9][MAX_STACK_HEIGHT];

void put_crates_at_bottom();

void parse_crates(char* current_line, int row) {
    // quick way of ignoring numbers
    if (current_line[C1_IDX] == '1') {
        put_crates_at_bottom();
        return;
    }

    crates[0][row] = current_line[C1_IDX];
    crates[1][row] = current_line[C2_IDX];
    crates[2][row] = current_line[C3_IDX];
    crates[3][row] = current_line[C4_IDX];
    crates[4][row] = current_line[C5_IDX];
    crates[5][row] = current_line[C6_IDX];
    crates[6][row] = current_line[C7_IDX];
    crates[7][row] = current_line[C8_IDX];
    crates[8][row] = current_line[C9_IDX];
}

void put_crates_at_bottom() {
    for (int i = 0; i < 9; i++) {
        crates[i][MAX_STACK_HEIGHT-1] = '\0';
        int bottom_index = MAX_STACK_HEIGHT-2;
        for (int j = MAX_STACK_HEIGHT-2; j > -1; j--) {
            if (crates[i][j] != ' ') {
                if (crates[i][j] == '\0') {
                    crates[i][j] = ' ';
                } else {
                    crates[i][bottom_index] = crates[i][j];
                    crates[i][j] = ' ';
                    bottom_index--;
                }
            }
        }
    }
}

void print_crates() {
    for (int i = 0; i < 9; i++) {
        printf("Row %d = %s\n", i, crates[i]);
    }
}

int get_top_crate_idx_on_stack(int stack) {
    for (int i = 0; i < MAX_STACK_HEIGHT; i++) {
        if (crates[stack][i] != ' ') {
            return i;
        }
    }

    printf("finding crates on empty stack %d\n", stack);
    exit(1);
}

void execute_move_part1(int num, int stack1, int stack2) {
    for (int i = 0; i < num; i++) {
        char crate_to_move = crates[stack1][get_top_crate_idx_on_stack(stack1)];
        int destination_target = get_top_crate_idx_on_stack(stack2);
        crates[stack2][destination_target-1] = crate_to_move;
        crates[stack1][get_top_crate_idx_on_stack(stack1)] = ' ';
    }

}

void execute_move(int num, int stack1, int stack2) {
    int target_start = get_top_crate_idx_on_stack(stack2) - num;

    int start_point = get_top_crate_idx_on_stack(stack1);

    for (int i = 0; i < num; i++) {
        char crate_to_move = crates[stack1][start_point + i];

        crates[stack2][target_start+i] = crate_to_move;
        crates[stack1][start_point+i] = ' '; 
    }

}

int main() {

    FILE *f = fopen("input5.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 512;

    int row = 0;
    int is_instructions = 0;
    while((getline(&current_line, &n, f)) > 0) {
        if (current_line[0] == '\n') {
            is_instructions = 1;
            continue;
        }
        if (!is_instructions) {
            parse_crates(current_line, row);
            row++;
        } else {
            int num, stack1, stack2;
            sscanf(current_line, "move %d from %d to %d", &num, &stack1, &stack2);
//            printf("parsed %d, %d, %d", num, stack1, stack2);
            execute_move(num, stack1-1, stack2-1);  // -1 cos I'm using 0 indexed array

        }
        
    }

    fclose(f);
    print_crates();
}
