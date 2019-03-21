#include "checker.h"
#include <stdlib.h>
#include <string.h>

static const int CHECKBOARD_WIDTH = 8;
static const int CHECKBOARD_HEIGHT = 8;

game *game_init(char *player_name1, char *player_name2) {
  game *g = malloc(sizeof(game));
  strncpy(g->players[0].name, player_name1, sizeof(g->players[0].name));
  strncpy(g->players[1].name, player_name2, sizeof(g->players[1].name));
  // (0, 0) is the top left corner
  for (int i = 0; i < CHECKER_COUNT; i++) {
    checker *c = &g->board.checkers[i];
    c->in_play = true;
    bool for_player2 = i >= CHECKER_COUNT / 2;
    int y_offset = for_player2 ? 2 : 0;
    c->player_index = for_player2 ? 1 : 0;
    c->y = i / 4 + y_offset;
    if (c->y % 2 == 0) {
      c->x = (((i + 1) * 2) - 1) % 8;
    } else {
      c->x = (i * 2) % 8;
    }
  }
  return g;
}

void game_free(game *game) { free(game); }

checker *game_find_piece(game *game, int x, int y) {
  if (x < 0 || x >= CHECKBOARD_WIDTH || y < 0 || y >= CHECKBOARD_HEIGHT) {
    return false;
  }
  for (int i = 0; i < CHECKER_COUNT; i++) {
    checker *c = &game->board.checkers[i];
    if (c->x == x && c->y == y) {
      return c;
    }
  }
  return NULL;
}

bool game_move_piece(game *g, checker *c, int x, int y) {
  if (g == NULL || c == NULL || x < 0 || x >= CHECKBOARD_WIDTH || y < 0 ||
      y >= CHECKBOARD_HEIGHT || (c->x == x && c->y == y) ||
      game_find_piece(g, x, y) != NULL) {
    return false;
  }
  // illegal backwards moves
  if (c->player_index == 0 && y <= c->y) {
    return false;
  }
  if (c->player_index == 1 && y >= c->y) {
    return false;
  }
  // move forward
  if (c->player_index == 0 && abs(x - c->x) == 1 && y == c->y + 1) {
    c->x = x;
    c->y = y;
    return true;
  }
  if (c->player_index == 1 && abs(x - c->x) == 1 && y == c->y - 1) {
    c->x = x;
    c->y = y;
    return true;
  }
  // jump piece
  checker *other = game_find_piece(g, x - 1, y + 1);
  if (x == c->x + 2 && y == c->y - 2 && other != NULL) {
    other->in_play = false;
    c->x = x;
    c->y = y;
    return true;
  }
  other = game_find_piece(g, x + 1, y + 1);
  if (x == c->x - 2 && y == c->y - 2 && other != NULL) {
    other->in_play = false;
    c->x = x;
    c->y = y;
    return true;
  }

  return false;
}

int game_pieces_in_play(game *game) {
  int in_play = 0;
  for (int i = 0; i < CHECKER_COUNT; i++) {
    checker *c = &game->board.checkers[i];
    if (c->in_play) {
      in_play++;
    }
  }

  return in_play;
}

int game_pieces_for_player(game *game, int player_index) {
  int in_play = 0;
  for (int i = 0; i < CHECKER_COUNT; i++) {
    checker *c = &game->board.checkers[i];
    if (c->in_play && c->player_index == player_index) {
      in_play++;
    }
  }

  return in_play;
}
