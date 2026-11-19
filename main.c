#include <stdio.h>

#include "display.h"
#include "game.h"
#include "input.h"

/* Plays one full game. Returns 0 if it ended normally, -1 if input was closed. */
static int play_game(void)
{
    Game game;
    game_init(&game);
    display_board(&game.board);

    while (!game_is_over(&game)) {
        int r1, c1, r2, c2, boxes;

        display_prompt(&game);
        InputStatus in = input_read_move(&r1, &c1, &r2, &c2);
        if (in == INPUT_EOF)
            return -1;
        if (in == INPUT_BAD_FORMAT) {
            printf("Invalid input: enter four numbers, e.g. 0 0 0 1\n");
            continue;
        }

        MoveStatus status = game_play_move(&game, r1, c1, r2, c2, &boxes);
        if (status != MOVE_OK) {
            display_move_error(status);
            continue;
        }

        display_scores(&game);
        display_board(&game.board);
    }

    display_result(&game);
    return 0;
}

int main(void)
{
    display_title();

    for (;;) {
        if (play_game() != 0)
            break;

        printf("Play again? (y/n): ");
        fflush(stdout);
        if (input_read_yes_no() != 1)
            break;
    }

    printf("Goodbye!\n");
    return 0;
}
