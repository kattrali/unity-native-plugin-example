#ifndef CHECKER_H
#define CHECKER_H
#include <stdbool.h>

// Number of checkers on the board
static const int CHECKER_COUNT = 24;

typedef struct player {
  char name[32];
} player;

typedef struct checker {
  int x;
  int y;
  bool is_king;
  bool in_play;
  int player_index;
} checker;

typedef struct checkerboard {
  checker checkers[CHECKER_COUNT];
} checkerboard;

typedef struct game {
  checkerboard board;
  player players[2];
} game;


/**
 * Create a new game
 */
game *game_init(char *player_name1, char *player_name2);

/**
 * Release game resources
 */
void game_free(game *game);

/**
 * Returns the checker instance in a given board location or NULL
 */
checker *game_find_piece(game *game, int x, int y);

/**
 * Returns true if the move succeeds
 */
bool game_move_piece(game *g, checker *c, int x, int y);

/**
 * Number of pieces still in play
 */
int game_pieces_in_play(game *g);

/**
 * Number of pieces still in play for a particular player
 */
int game_pieces_for_player(game *g, int player_index);
#endif // CHECKER_H
