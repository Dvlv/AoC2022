#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int x = 1;

int notable_cycles[6];
int n_cyc_idx = 0;

char pixels[240];

int cycle_num = 1;





int next_cyc_target = 0;
int next_cyc_amt = 0;

int processing = 0;

void modify_x(int amt) {
    x += amt;
}

void draw_current_pixel() {
    if (cycle_num > 239) {
        printf("Gone too far!\n");
        exit(1);
    }

    int cyc_idx = cycle_num-1;

    while (cyc_idx >= 40) {
        cyc_idx -= 40;
    }

    if (x == cyc_idx ||
     (x == (cyc_idx - 1) && cyc_idx > 0) ||
     (x == (cyc_idx + 1) && cyc_idx < 40) 
     ) {
        pixels[cycle_num-1] = '#';
     } else {
        pixels[cycle_num-1] = '.';
     }

    printf("cycle index %d, x %d\n", cyc_idx, x);
}

void end_of_cycle() {
    // must be a better way
    // if (cycle_num == 20 || cycle_num == 60 || cycle_num == 100 || cycle_num == 140 || cycle_num == 180 || cycle_num == 220) {
    //     notable_cycles[n_cyc_idx] = x;
    //     n_cyc_idx++;
    // }

    draw_current_pixel();

    if (cycle_num == next_cyc_target) {
        modify_x(next_cyc_amt);
        next_cyc_amt = 0;
        next_cyc_target = 0;
        processing = 0;
    }

    //printf("end of cycle %d, x is %d\n", cycle_num, x);
    cycle_num++;
}

void print_notable() {
    for (int i = 0; i < 6; i++) {
        printf("notable %d = %d\n", i, notable_cycles[i]);
    }

    int sum_str = notable_cycles[0] * 20 + notable_cycles[1] * 60 + notable_cycles[2] * 100 + notable_cycles[3] * 140 + notable_cycles[4] * 180 + notable_cycles[5] * 220;
    printf("sum str %d\n", sum_str);
}

void print_screen() {
    for (int i = 0; i < 240; i++) {
        printf("%c", pixels[i]);
        if ((i+1) % 40 == 0 && i > 0) printf("\n");
    }
}

int main() {

    FILE *f = fopen("input10.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 100;

    while (cycle_num < 240)
    { // TODO 220
        printf("start cycle %d\n", cycle_num);
        if (cycle_num > 240)
            break;
        if (processing)
        {
            end_of_cycle();
        }
        else
        {
            if ((getline(&current_line, &n, f)) > 0)
                {
                    if (strcmp(current_line, "noop\n") == 0)
                    {
                        end_of_cycle();
                    }
                    else
                    {
                        int amt;
                        sscanf(current_line, "addx %d", &amt);

                        next_cyc_target = cycle_num + 1;
                        next_cyc_amt = amt;
                        processing = 1;
                        end_of_cycle();
                    }
                }
        }
    }

    fclose(f);
    print_screen();
}