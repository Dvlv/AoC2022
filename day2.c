#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN 1
#define DRAW 0
#define LOSE -1

int get_game_result(char my_move, char opponent_move) {
    if (my_move == 'A') {
        if (opponent_move == 'A') return DRAW;
        if (opponent_move == 'B') return LOSE;
        if (opponent_move == 'C') return WIN;

        printf("parsed unknown opp move %c", opponent_move);
        exit(1);
    }

    if (my_move == 'B') {
        if (opponent_move == 'A') return WIN;
        if (opponent_move == 'B') return DRAW;
        if (opponent_move == 'C') return LOSE;

        printf("parsed unknown opp move %c", opponent_move);
        exit(1);
    }

    if (my_move == 'C') {
        if (opponent_move == 'A') return LOSE;
        if (opponent_move == 'B') return WIN;
        if (opponent_move == 'C') return DRAW;

        printf("parsed unknown opp move %c", opponent_move);
        exit(1);
    }

    printf("parsed unknown move %c", my_move);
    exit(1);
}

char get_my_move_to_play(char opp_move, char expected_res) {
    if (expected_res == 'X') {
        if (opp_move == 'A') return 'C';
        if (opp_move == 'B') return 'A';
        if (opp_move == 'C') return 'B';

        printf("parsed unknown opp move %c", opp_move);
        exit(1);

    }
    if (expected_res == 'Y') {
        if (opp_move == 'A') return 'A';
        if (opp_move == 'B') return 'B';
        if (opp_move == 'C') return 'C';

        printf("parsed unknown opp move %c", opp_move);
        exit(1);

    }
    if (expected_res == 'Z') {
        if (opp_move == 'A') return 'B';
        if (opp_move == 'B') return 'C';
        if (opp_move == 'C') return 'A';

        printf("parsed unknown opp move %c", opp_move);
        exit(1);
    }

    printf("parsed unknown result %c", expected_res);
    exit(1);

}

int get_score_from_moves(char my_move, char opp_move) {
    int sc = 0;

    int result = get_game_result(my_move, opp_move);
    if (result == WIN) {
        sc = 6;
    } else if (result == DRAW) {
        sc = 3;
    }

    if (my_move == 'A') sc += 1;
    if (my_move == 'B') sc += 2;        
    if (my_move == 'C') sc += 3;        

    return sc;
}

int main() {
    FILE *f = fopen("input2.txt", "r");

    if (f == NULL) {
        printf("Failed to open file!");
        return 1;
    }

    char *current_line;
    size_t n = 255;

    int score = 0;

    char my_move;
    char opponent_move;
    char ws;
    char expected_res;
    while ((fscanf(f, "%c%c%c\n", &opponent_move, &ws, &expected_res )) != EOF) {
        printf("Opp playing %c, Expected res %c", opponent_move, expected_res);
        char my_move = get_my_move_to_play(opponent_move, expected_res);

        printf("; Playing %c\n", my_move);

        score += get_score_from_moves(my_move, opponent_move);
    }

    printf("Score: %d\n", score);
    fclose(f);

} 