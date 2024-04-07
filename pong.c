#include <stdio.h>

#define LINE 25
#define COLUMN 80

void pseudo_clean_screen();
void initialize_game();
void game();
int change_ball_direction(int current_player);

int main(void) {
    char user_input;
    initialize_game();

    while (1) {
        user_input = getchar();
        pseudo_clean_screen();
        if (user_input == '1') game();
        else if (user_input == 'q' || user_input == 'Q') return 0;
        else initialize_game();
    }
}

void pseudo_clean_screen() {
    for (int i=0; i < 10; i++) printf("\n");
}

void initialize_game() {
    printf("Hi! Print \"1\" to start the game; print \"Q\" to quit.\n");
    printf("---------------------\n");
    printf("This is simplified version of one of the first arcade games.\n");
    printf("Players take turns, each move moving their racket one square down or up\n");
    printf("Let the most patient win :).\n");
    printf("---------------------\n");
    printf("1st Player controls: A - up; Z - down.\n");
    printf("1st Player controls: K - up; M - down.\n");
}

void game() {

    int p1_score = 0;
    int p2_score = 0;

    int p1_pos = 12;
    int p2_pos = 12;

    int ball_lin = 12;
    int ball_col = 39;
    int ball_x_axis = -1;
    int ball_y_axis = 1;

    int current_player = 1;

    char input;

    while (input = getchar()) {
        if (input == 'Q' || input == 'q') break;

        /*
         * Очистка экрана.
         */
//        pseudo_clean_screen();

        /*
         * Блок управления.
         * switch при желании меняем на if.
         */
        switch (input) {
            case 'a': case 'A':
                p1_pos = p1_pos <= 2 ? p1_pos : p1_pos - 1;
                current_player = 2;
                break;
            case 'z' : case 'Z':
                p1_pos = p1_pos >= LINE - 3 ? p1_pos : p1_pos + 1;
                current_player = 2;
                break;
            case 'k': case 'K':
                p2_pos = p2_pos <= 2 ? p2_pos : p2_pos - 1;
                current_player = 1;
                break;
            case 'm' : case 'M':
                p2_pos = p2_pos >= LINE - 3 ? p2_pos : p2_pos + 1;
                current_player = 1;
                break;
            case 'q': case 'Q':
                return;
                break;
            default:
                printf("Q - quit; A/Z - player 1 up-down; K/M - player 2 ud-down.\n");
                break;
        }

        /*
         * Блок движений мяча (в зависимости от значений оси координат).
         */
        if (ball_x_axis = 1) ball_col++;
        if (ball_x_axis = -1) ball_col--;
        if (ball_y_axis = 1) ball_lin++;
        if (ball_y_axis = -1) ball_lin--;

        /*
         * Блок отскока мяча от стен.
         */
        if (ball_lin <= 1) ball_y_axis = 1;
        if (ball_lin >= LINE - 2) ball_y_axis = -1;

        /*
         * Блок отскока мяча от ракеток.
         */
        if (ball_col <= 3 && (ball_lin == p1_pos - 1 || ball_lin == p1_pos || ball_lin == p1_pos + 1)) {
            ball_x_axis = 1;
        }
        if (ball_col >= COLUMN - 4 && (ball_lin == p2_pos - 1 || ball_lin == p2_pos || ball_lin == p2_pos + 1)) {
            ball_x_axis = -1;
        }

        /*
         * Блок ворот (если мяч попадает в левые или правые ворота).
         */
        if (ball_col <= 2) {
            p2_score++;
            ball_lin = 12;
            ball_col = 39;
            ball_x_axis = change_ball_direction(1);
            ball_y_axis = change_ball_direction(1);
        }
        if (ball_col >= COLUMN - 2) {
            p1_score++;
            ball_lin = 12;
            ball_col = 39;
            ball_x_axis = change_ball_direction(2);
            ball_y_axis = change_ball_direction(2);
        }

        /*
         * Далее идёт блок отрисовки игры
         */
        printf("\n");
        printf("---------------[ %-2d ]=========+++ TACTIC PONG +++=========[ %2d ]---------------\n", p1_score, p2_score);
        for (int lin = 0; lin < LINE; lin++) {
            for (int col = 0; col < COLUMN; col++){
                if (!lin || lin == LINE - 1) {
                    printf("#");
                } else if (col == ball_col && lin == ball_lin) {
                    printf("O");
                } else if (!col || col == COLUMN - 1) {
                    printf("|");
                } else if (col == COLUMN / 2 || col == COLUMN / 2 - 1) {
                    printf(":");
                } else if (col == 2 && (lin == p1_pos - 1 || lin == p1_pos || lin == p1_pos + 1)) {
                    printf("I");
                } else if (col == COLUMN - 3 && (lin == p2_pos - 1 || lin == p2_pos || lin == p2_pos + 1)) {
                    printf("I");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("%dst player turn: ", current_player);
    }

}

int change_ball_direction(int current_player) {
    return current_player % 2 ? 1 : -1;
}