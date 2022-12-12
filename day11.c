#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_MONKEY_ITEMS 20
#define OLD_TIMES_OLD_INT -1

typedef struct monkey {
    int items[MAX_MONKEY_ITEMS];
    char operator;
    int operation;
    int divisor;
    int throw_true;
    int throw_false;
} monkey_t;

monkey_t monkeys[8];
int cur_m_idx = 0;


void print_monkey(monkey_t *m) {
    printf("Items: ");
    for (int i =0; i < MAX_MONKEY_ITEMS;i++) {
        printf("%d, ", m->items[i]);
    }
    printf("op: %c, opr: %d, div: %d, tt: %d, tf: %d\n", m->operator, m->operation, m->divisor, m->throw_true, m->throw_false);
}

void shift_monkey_items_fwd(monkey_t *m) {
    int first_non_zero = MAX_MONKEY_ITEMS;

    for (int i =0; i < MAX_MONKEY_ITEMS;i++) {
        if (m->items[i] != 0) {
            if (i == 0) return;

            first_non_zero = i;
            break;
        }
    }

    int new_idx = 0;
    for (int i = first_non_zero; i < MAX_MONKEY_ITEMS; i++) {
        m->items[new_idx] = m->items[i];
        new_idx++;
    }
}

void add_to_end_of_money_items(monkey_t *m, int item) {
    for (int i =0; i < MAX_MONKEY_ITEMS;i++) {
        if (m->items[i] == 0) {
            m->items[i] = item;
            return;
        }
    }

    printf("Monkey has no more item space!\n");
    exit(1);

}

void monkey_throw_item(monkey_t *m1, int item_idx, monkey_t *m2) {
    add_to_end_of_money_items(m2, m1->items[item_idx]);
    m1->items[item_idx] = 0;
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

        int si[MAX_MONKEY_ITEMS] = {0};
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
        int opr;
        getline(&current_line, &n, f);
        if (strchr(current_line, '+') != NULL) {
            op = '+';
            sscanf(current_line, "  Operation: new = old + %d", &opr);
        } else {
            op = '*';
            if (strstr(current_line, "old * old") != NULL) {
                opr = OLD_TIMES_OLD_INT;
            } else {
                sscanf(current_line, "  Operation: new = old * %d", &opr);
            }
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

        monkey_t m = {.operator=op, .operation=opr, .divisor=test, .throw_true=tm, .throw_false=fm};
        for (int j = 0; j < MAX_MONKEY_ITEMS; j++) {
            m.items[j] = si[j];
        }
        monkeys[i] = m;
        getline(&current_line, &n, f); // blank line
    }

    for (int i = 0; i < 8; i++) {
        print_monkey(&monkeys[i]);
    }

    fclose(f);
}