#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct monkey {
    int items[20];
    char operator;
    int divisor;
    int throw_true;
    int throw_false;
} monkey_t;

monkey_t monkeys[8];
int cur_m_idx = 0;


void print_monkey(monkey_t *m) {
    printf("op: %c, div: %d, tt: %d, tf: %d\n", m->operator, m->divisor, m->throw_true, m->throw_false);
}


int main() {

    FILE *f = fopen("input11.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line = (char *)malloc(200);
    size_t n = 200;

    int id = 0;
    for (int i = 0; i < 8; i++) {
        getline(&current_line, &n, f); // id
        getline(&current_line, &n, f); // starting items

        // starting items
        char cl[100];
        strncpy (cl, current_line, 99);
        cl[99] = '\0';

        char *token = strtok(cl, ",");
        int first_num = atoi(&token[18]);
        token = strtok(NULL, ",");

        int si[20];
        int si_idx = 0;
        si[si_idx] = first_num;
        si_idx++;

        while (token != NULL) {
            int nn = atoi(token);
            si[si_idx] = nn;
            si_idx++;
            token = strtok(NULL, ",");
        }

        // operator
        char op;
        getline(&current_line, &n, f);
        if (strchr(current_line, '+') != NULL) {
            op = '+';
        } else {
            op = '*';
        }

        // test
        int test;
        getline(&current_line, &n, f);
        sscanf(current_line, "  Test: divisible by %d", &test);

        // true monkey
        int tm;
        getline(&current_line, &n, f);
        sscanf(current_line, "    If true: throw to monkey %d", &tm);

        // false monkey
        int fm;
        getline(&current_line, &n, f);
        sscanf(current_line, "    If false: throw to monkey %d", &fm);

        monkey_t m = {.items=si, .operator=op, .divisor=test, .throw_true=tm, .throw_false=fm};
        monkeys[cur_m_idx] = m;
    }

    for (int i = 0; i < 8; i++) {
        print_monkey(&monkeys[i]);
    }

    fclose(f);
}