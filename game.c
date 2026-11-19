#include "game.h"

void game_init(Game *g)
{
    board_init(&g->board);
    for (int i = 0; i < NUM_PLAYERS; i++)
        g->score[i] = 0;
    g->current = 0;
}

char game_player_letter(int player)
{
    return (char)('A' + player);
}

MoveStatus game_play_move(Game *g, int r1, int c1, int r2, int c2, int *boxes_completed)
{
    MoveStatus status = board_draw_line(&g->board, r1, c1, r2, c2,
                                        game_player_letter(g->current), boxes_completed);
    if (status != MOVE_OK)
        return status;

    if (*boxes_completed > 0)
        g->score[g->current] += *boxes_completed;
    else
        g->current = (g->current + 1) % NUM_PLAYERS;

    return MOVE_OK;
}

bool game_is_over(const Game *g)
{
    return g->score[0] + g->score[1] == TOTAL_BOXES;
}

int game_winner(const Game *g)
{
    if (g->score[0] > g->score[1])
        return 0;
    if (g->score[1] > g->score[0])
        return 1;
    return -1;
}
