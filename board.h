#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

/* The game is played on a 4x5 grid of boxes, i.e. 5 rows x 6 columns of dots. */
#define BOX_ROWS 4
#define BOX_COLS 5
#define DOT_ROWS (BOX_ROWS + 1)
#define DOT_COLS (BOX_COLS + 1)
#define TOTAL_BOXES (BOX_ROWS * BOX_COLS)

#define NO_OWNER ' '

typedef struct {
    /* h[r][c] is the horizontal line from dot (r, c) to dot (r, c + 1). */
    bool h[DOT_ROWS][BOX_COLS];
    /* v[r][c] is the vertical line from dot (r, c) to dot (r + 1, c). */
    bool v[BOX_ROWS][DOT_COLS];
    /* owner[r][c] is 'A', 'B' or NO_OWNER for the box whose top-left dot is (r, c). */
    char owner[BOX_ROWS][BOX_COLS];
} Board;

typedef enum {
    MOVE_OK,
    MOVE_OUT_OF_RANGE,   /* a dot is outside the grid */
    MOVE_NOT_ADJACENT,   /* the two dots are not neighbours */
    MOVE_ALREADY_DRAWN   /* the line already exists */
} MoveStatus;

void board_init(Board *b);

/*
 * Draws the line between dots (r1, c1) and (r2, c2) for `player`.
 * On MOVE_OK, every box the line completes is given to `player`, and the number
 * of boxes completed (0, 1 or 2) is stored in *boxes_completed.
 * On any other status the board is left unchanged.
 */
MoveStatus board_draw_line(Board *b, int r1, int c1, int r2, int c2,
                           char player, int *boxes_completed);

/* True when all four sides of box (r, c) are drawn. O(1). */
bool board_box_complete(const Board *b, int r, int c);

int board_claimed_count(const Board *b);

#endif
