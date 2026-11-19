#include "board.h"

#include <stdlib.h>

void board_init(Board *b)
{
    for (int r = 0; r < DOT_ROWS; r++)
        for (int c = 0; c < BOX_COLS; c++)
            b->h[r][c] = false;

    for (int r = 0; r < BOX_ROWS; r++)
        for (int c = 0; c < DOT_COLS; c++)
            b->v[r][c] = false;

    for (int r = 0; r < BOX_ROWS; r++)
        for (int c = 0; c < BOX_COLS; c++)
            b->owner[r][c] = NO_OWNER;
}

static bool dot_in_range(int r, int c)
{
    return r >= 0 && r < DOT_ROWS && c >= 0 && c < DOT_COLS;
}

bool board_box_complete(const Board *b, int r, int c)
{
    return b->h[r][c] && b->h[r + 1][c] && b->v[r][c] && b->v[r][c + 1];
}

/* Gives box (r, c) to `player` if it exists, is unclaimed and is now complete. */
static int try_claim(Board *b, int r, int c, char player)
{
    if (r < 0 || r >= BOX_ROWS || c < 0 || c >= BOX_COLS)
        return 0;
    if (b->owner[r][c] != NO_OWNER || !board_box_complete(b, r, c))
        return 0;
    b->owner[r][c] = player;
    return 1;
}

MoveStatus board_draw_line(Board *b, int r1, int c1, int r2, int c2,
                           char player, int *boxes_completed)
{
    *boxes_completed = 0;

    if (!dot_in_range(r1, c1) || !dot_in_range(r2, c2))
        return MOVE_OUT_OF_RANGE;

    if (r1 == r2 && abs(c1 - c2) == 1) {
        /* Horizontal line: it can close the box above it and the box below it. */
        int c = c1 < c2 ? c1 : c2;
        if (b->h[r1][c])
            return MOVE_ALREADY_DRAWN;
        b->h[r1][c] = true;
        *boxes_completed += try_claim(b, r1 - 1, c, player);
        *boxes_completed += try_claim(b, r1, c, player);
        return MOVE_OK;
    }

    if (c1 == c2 && abs(r1 - r2) == 1) {
        /* Vertical line: it can close the box to its left and the box to its right. */
        int r = r1 < r2 ? r1 : r2;
        if (b->v[r][c1])
            return MOVE_ALREADY_DRAWN;
        b->v[r][c1] = true;
        *boxes_completed += try_claim(b, r, c1 - 1, player);
        *boxes_completed += try_claim(b, r, c1, player);
        return MOVE_OK;
    }

    return MOVE_NOT_ADJACENT;
}

int board_claimed_count(const Board *b)
{
    int count = 0;
    for (int r = 0; r < BOX_ROWS; r++)
        for (int c = 0; c < BOX_COLS; c++)
            if (b->owner[r][c] != NO_OWNER)
                count++;
    return count;
}
