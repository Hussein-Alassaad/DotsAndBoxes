#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "board.h"

#define NUM_PLAYERS 2

typedef struct {
    Board board;
    int score[NUM_PLAYERS];  /* score[0] is player A, score[1] is player B */
    int current;             /* index of the player whose turn it is */
} Game;

void game_init(Game *g);

/* 'A' for player 0, 'B' for player 1. */
char game_player_letter(int player);

/*
 * Plays a move for the current player. If it completes at least one box the
 * player scores and plays again; otherwise the turn passes to the other player.
 */
MoveStatus game_play_move(Game *g, int r1, int c1, int r2, int c2, int *boxes_completed);

bool game_is_over(const Game *g);

/* Index of the winning player, or -1 for a tie. */
int game_winner(const Game *g);

#endif
