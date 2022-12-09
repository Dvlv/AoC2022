#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VISITED_POINTS_LEN 9000

typedef struct point {
    int x;
    int y;
} point_t;

point_t* visited[MAX_VISITED_POINTS_LEN];
int visited_index = 0;

int has_point_been_visited_already(int x, int y) {
        //printf("checking point (%d,%d)\n", x, y);
    for (int i = 0; i < MAX_VISITED_POINTS_LEN; i++) {
        point_t *p = visited[i];

        if (p == NULL) {
            break;
        }

        if (p->x == x && p->y == y) {
            return 1;
        }
    }

    return 0;
}

void add_visited_point(int x, int y) {
    if (!has_point_been_visited_already(x, y)) {
        point_t *new_point = (point_t*) malloc(sizeof(point_t));
        new_point->x = x;
        new_point->y = y;

        //printf("adding point (%d,%d)\n", x, y);
        
        visited[visited_index] = new_point;
        visited_index++;
    }
}

void move_h(point_t *current_h, char dir) {
    if (dir == 'R') {
        current_h->x+= 1;
    } else if (dir == 'L') {
        current_h->x -= 1;
    } else if (dir == 'U') {
        //printf("adding one to h's y, currently %d", current_h->y);
        current_h->y += 1;
        //printf(" after %d\n", current_h->y);
    } else if (dir == 'D') {
        current_h->y -= 1;
    } else {
        printf("Got unexpected dir %c", dir);
        exit(1);
    }

}

int is_diag_touching(point_t *current_h, point_t *current_t) {
    int xdiff = current_h->x - current_t->x;
    int ydiff = current_h->y - current_t->y;
    // I should learn how to do abs
    if (abs(xdiff) < 2 && abs(ydiff) < 2) {
        return 1;
    }
    return 0;
}

void move_t_based_on_h(point_t *current_t, point_t *current_h) {
    //printf("before move_t, h is (%d,%d) ;", current_h->x, current_h->y);
    // diagonally
    if (current_h->x != current_t->x && current_h->y != current_t->y) {
        if (is_diag_touching(current_h, current_t)) return;
        int xmov = current_h->x > current_t->x ? 1 : -1;
        int ymov = current_h->y > current_t->y ? 1 : -1;

        current_t->x += xmov;
        current_t->y += ymov;
        return;
    }

    // 2 steps right
    if (current_h->x > (current_t->x + 1)) {
        current_t->x += 1;
        return;
    }

    // 2 steps left
    if (current_h->x < (current_t->x - 1)) {
        current_t->x -= 1;
        return;
    }

    // 2 steps down
    if (current_h->y < (current_t->y - 1)) {
        current_t->y -= 1;
        return;
    }

    // 2 steps up
    if (current_h->y > (current_t->y + 1)) {
        current_t->y += 1;
        return;
    }
}

void process_move(point_t *current_h, point_t *current_t, char dir, int amt) {
        //printf("--- %d %c ---\n", amt, dir);
    for (int i = 0; i < amt; i++) {
        move_h(current_h, dir);
        move_t_based_on_h(current_t, current_h);
        //printf("after move_t, h is (%d,%d) ;", current_h->x, current_h->y);
        add_visited_point(current_t->x, current_t->y);
        //printf("H to (%d,%d) ; ", current_h->x, current_h->y);
        //printf("T to (%d,%d)\n", current_t->x, current_t->y);
    }

}

int count_visited() {
    int count = 0;
    for (int i = 0; i < MAX_VISITED_POINTS_LEN; i++) {
        if (visited[i] != NULL) {
            count++;
        }
    }

    return count;
}


int main() {

    FILE *f = fopen("input9.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 100;

    point_t current_h = {.x = 0, .y = 0};
    point_t current_t = {.x = 0, .y = 0};

    while((getline(&current_line, &n, f)) > 0) {
        char dir;
        int amt;
        sscanf(current_line, "%c %d", &dir, &amt);
        process_move(&current_h, &current_t, dir, amt);
    }

    fclose(f);

    int pv = count_visited();
    printf("visited index %d\n", visited_index);

    // 8728 too high;

    printf("points visited by t: %d\n", pv);
}