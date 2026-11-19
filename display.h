#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

void display_title(void);
void display_board(const Board *b);
void display_scores(const Game *g);
void display_prompt(const Game *g);
void display_move_error(MoveStatus status);
void display_result(const Game *g);

#endif
