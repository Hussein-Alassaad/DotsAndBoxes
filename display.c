#include "display.h"

#include <stdio.h>

#define SEPARATOR "**********************************************************************"

void display_title(void)
{
    printf("%s\n", SEPARATOR);
    printf("                         DOTS AND BOXES\n");
    printf("  Players A and B take turns drawing a line between two neighbouring dots.\n");
    printf("  Complete a box to claim it and play again. Most boxes wins.\n");
    printf("%s\n", SEPARATOR);
}

/*
 * Example of the layout (matches the course handout):
 *
 *   0 1 2 3 4 5
 * 0 .-.-. . . .
 *   |A| |
 * 1 .-.-. . . .
 */
void display_board(const Board *b)
{
    printf("  ");
    for (int c = 0; c < DOT_COLS; c++)
        printf("%d ", c);
    printf("\n");

    for (int r = 0; r < DOT_ROWS; r++) {
        /* Row of dots with the horizontal lines between them. */
        printf("%d ", r);
        for (int c = 0; c < DOT_COLS; c++) {
            putchar('.');
            if (c < BOX_COLS)
                putchar(b->h[r][c] ? '-' : ' ');
        }
        printf("\n");

        if (r == BOX_ROWS)
            break;

        /* Row of vertical lines with the box owners between them. */
        printf("  ");
        for (int c = 0; c < DOT_COLS; c++) {
            putchar(b->v[r][c] ? '|' : ' ');
            if (c < BOX_COLS)
                putchar(b->owner[r][c]);
        }
        printf("\n");
    }
}

void display_scores(const Game *g)
{
    printf("%s\n", SEPARATOR);
    for (int i = 0; i < NUM_PLAYERS; i++)
        printf("Player %c score: %d\n", game_player_letter(i), g->score[i]);
    printf("%s\n", SEPARATOR);
}

void display_prompt(const Game *g)
{
    printf("Player %c's turn. Enter the row and column of the first dot "
           "(e.g., A0 -> 0 0) and second dot:\n", game_player_letter(g->current));
}

void display_move_error(MoveStatus status)
{
    switch (status) {
    case MOVE_OUT_OF_RANGE:
        printf("Invalid move: rows go from 0 to %d and columns from 0 to %d.\n",
               DOT_ROWS - 1, DOT_COLS - 1);
        break;
    case MOVE_NOT_ADJACENT:
        printf("Invalid move: the two dots must be next to each other "
               "(same row or same column, one step apart).\n");
        break;
    case MOVE_ALREADY_DRAWN:
        printf("Invalid move: that line is already drawn.\n");
        break;
    case MOVE_OK:
        break;
    }
}

void display_result(const Game *g)
{
    int winner = game_winner(g);

    printf("%s\n", SEPARATOR);
    printf("GAME OVER! Final score: A %d - B %d\n", g->score[0], g->score[1]);
    if (winner < 0)
        printf("It's a tie!\n");
    else
        printf("Player %c wins!\n", game_player_letter(winner));
    printf("%s\n", SEPARATOR);
}
