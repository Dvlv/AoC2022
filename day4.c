#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int range_contains(r1s, r1f, r2s, r2f) {
	if (r2s >= r1s && r2f <= r1f) {
		return 1;
	}
	if (r1s >= r2s && r1f <= r2f) {
		return 1;
	}

	return 0;
}

int overlaps(int r1s, int r1f, int r2s, int r2f) {
	if (r2s <= r1f && r2f >= r1f) {
		// 2 overlaps 1
		return 1;
	}
	if (r1s <= r2f && r1f >= r2f) {
		// 1 overlaps 2
		return 1;
	}

	return 0;
}

int main() {

    FILE *f = fopen("input4.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 255;

    int num_contains = 0;
    int num_overlaps = 0;

    while((getline(&current_line, &n, f)) > 0) {
	int e1_s, e1_f, e2_s, e2_f;
	sscanf(current_line, "%d-%d,%d-%d", &e1_s, &e1_f, &e2_s, &e2_f);

	//if (range_contains(e1_s, e1_f, e2_s, e2_f)) {
		//num_contains++;
	//}
	if (overlaps(e1_s, e1_f, e2_s, e2_f)) {
		num_overlaps++;
	}
    }

    fclose(f);
    printf("%d overlaps\n", num_overlaps);
}
