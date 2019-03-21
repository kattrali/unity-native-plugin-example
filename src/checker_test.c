#include "checker.h"
#include <greatest/greatest.h>

TEST init_player_piece_assignment(void) {
  game *g = game_init("sue", "bob");
  for (int i = 0; i < 12; i++) {
    checker c = g->board.checkers[i];
    ASSERT_EQ_FMT(0, c.player_index, "%d");
    ASSERT_EQm("Piece is not in play", true, c.in_play);
  }
  for (int i = 12; i < 24; i++) {
    ASSERT_EQ_FMT(1, g->board.checkers[i].player_index, "%d");
  }

  free(g);
  PASS();
}

TEST init_correct_checker_positions_player1(void) {
  game *g = game_init("sue", "bob");
  ASSERT_EQ(1, g->board.checkers[0].x);
  ASSERT_EQ(0, g->board.checkers[0].y);
  ASSERT_EQ(3, g->board.checkers[1].x);
  ASSERT_EQ(0, g->board.checkers[1].y);
  ASSERT_EQ(5, g->board.checkers[2].x);
  ASSERT_EQ(0, g->board.checkers[2].y);
  ASSERT_EQ(7, g->board.checkers[3].x);
  ASSERT_EQ(0, g->board.checkers[3].y);
  ASSERT_EQ(0, g->board.checkers[4].x);
  ASSERT_EQ(2, g->board.checkers[5].x);
  ASSERT_EQ(1, g->board.checkers[5].y);
  ASSERT_EQ(4, g->board.checkers[6].x);
  ASSERT_EQ(1, g->board.checkers[6].y);
  ASSERT_EQ(6, g->board.checkers[7].x);
  ASSERT_EQ(1, g->board.checkers[7].y);
  ASSERT_EQ(1, g->board.checkers[8].x);
  ASSERT_EQ(2, g->board.checkers[8].y);
  ASSERT_EQ(3, g->board.checkers[9].x);
  ASSERT_EQ(2, g->board.checkers[9].y);
  ASSERT_EQ(5, g->board.checkers[10].x);
  ASSERT_EQ(2, g->board.checkers[10].y);
  ASSERT_EQ(7, g->board.checkers[11].x);
  ASSERT_EQ(2, g->board.checkers[11].y);

  free(g);
  PASS();
}

TEST init_correct_checker_positions_player2(void) {
  game *g = game_init("sue", "bob");
  ASSERT_EQ(0, g->board.checkers[12].x);
  ASSERT_EQ(5, g->board.checkers[12].y);
  ASSERT_EQ(2, g->board.checkers[13].x);
  ASSERT_EQ(5, g->board.checkers[13].y);
  ASSERT_EQ(4, g->board.checkers[14].x);
  ASSERT_EQ(5, g->board.checkers[14].y);
  ASSERT_EQ(6, g->board.checkers[15].x);
  ASSERT_EQ(5, g->board.checkers[15].y);
  ASSERT_EQ(1, g->board.checkers[16].x);
  ASSERT_EQ(6, g->board.checkers[16].y);
  ASSERT_EQ(3, g->board.checkers[17].x);
  ASSERT_EQ(6, g->board.checkers[17].y);
  ASSERT_EQ(5, g->board.checkers[18].x);
  ASSERT_EQ(6, g->board.checkers[18].y);
  ASSERT_EQ(7, g->board.checkers[19].x);
  ASSERT_EQ(6, g->board.checkers[19].y);
  ASSERT_EQ(0, g->board.checkers[20].x);
  ASSERT_EQ(7, g->board.checkers[20].y);
  ASSERT_EQ(2, g->board.checkers[21].x);
  ASSERT_EQ(7, g->board.checkers[21].y);
  ASSERT_EQ(4, g->board.checkers[22].x);
  ASSERT_EQ(7, g->board.checkers[22].y);
  ASSERT_EQ(6, g->board.checkers[23].x);
  ASSERT_EQ(7, g->board.checkers[23].y);
  free(g);
  PASS();
}

TEST init_player_names(void) {
  game *g = game_init("sue", "bob");
  ASSERT_STR_EQ(g->players[0].name, "sue");
  ASSERT_STR_EQ(g->players[1].name, "bob");
  free(g);
  PASS();
}

TEST find_piece(void) {
  game *g = game_init("sue", "bob");
  ASSERT(game_find_piece(g, 0, 0) == NULL);
  ASSERT(game_find_piece(g, 1, 0) != NULL);
  ASSERT(game_find_piece(g, 6, 6) == NULL);
  ASSERT(game_find_piece(g, 6, 7) != NULL);
  free(g);
  PASS();
}

TEST move_piece_in_place(void) {
  game *g = game_init("sue", "bob");
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 2, 1), 2, 1));
  free(g);
  PASS();
}

TEST move_piece_horizontally(void) {
  game *g = game_init("sue", "bob");
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 2, 1), 3, 1));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 2, 1), 1, 1));
  free(g);
  PASS();
}

TEST move_piece_too_far(void) {
  game *g = game_init("sue", "bob");
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 1, 0), 1, 2));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 1, 0), 1, 0));
  free(g);
  PASS();
}

TEST move_piece_backwards(void) {
  game *g = game_init("sue", "bob");
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 1, 2), 1, 1));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 1, 2), 1, 0));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 0, 5), 0, 6));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 0, 5), 0, 7));
  free(g);
  PASS();
}

TEST jump_piece(void) {
  game *g = game_init("sue", "bob");
  checker *c1 = game_find_piece(g, 1, 2);
  c1->y = 4;
  checker *c2 = game_find_piece(g, 0, 5);

  ASSERT(game_move_piece(g, c2, 2, 3));
  ASSERT_FALSE(c1->in_play);
  ASSERT_EQ(2, c2->x);
  ASSERT_EQ(3, c2->y);
  free(g);
  PASS();
}

TEST jump_piece_backward(void) {
  game *g = game_init("sue", "bob");
  checker *c1 = game_find_piece(g, 1, 2);
  c1->y = 4;
  checker *c2 = game_find_piece(g, 0, 5);
  c2->x = 2;
  c2->y = 3;

  ASSERT_FALSE(game_move_piece(g, c2, 0, 5));
  ASSERT(c1->in_play);
  ASSERT_EQ(2, c2->x);
  ASSERT_EQ(3, c2->y);
  free(g);
  PASS();
}

TEST jump_piece_same_color(void) {
  game *g = game_init("sue", "bob");
  checker *c1 = game_find_piece(g, 1, 2);
  checker *c2 = game_find_piece(g, 0, 1);
  c2->x = 2;
  c2->y = 3;

  ASSERT_FALSE(game_move_piece(g, c1, 3, 4));
  ASSERT(c2->in_play);
  ASSERT_EQ(2, c2->x);
  ASSERT_EQ(3, c2->y);
  free(g);
  PASS();
}

TEST move_forward(void) {
  game *g = game_init("sue", "bob");
  ASSERT(game_move_piece(g, game_find_piece(g, 1, 2), 2, 3));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 2, 3), 1, 2));
  ASSERT(game_move_piece(g, game_find_piece(g, 0, 5), 1, 4));
  ASSERT_FALSE(game_move_piece(g, game_find_piece(g, 1, 4), 0, 5));

  free(g);
  PASS();
}

TEST kingmaking(void) {

  PASS();
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();

  RUN_TEST(init_correct_checker_positions_player1);
  RUN_TEST(init_correct_checker_positions_player2);
  RUN_TEST(init_player_names);
  RUN_TEST(init_player_piece_assignment);
  RUN_TEST(find_piece);
  RUN_TEST(move_piece_horizontally);
  RUN_TEST(move_piece_backwards);
  RUN_TEST(move_piece_too_far);
  RUN_TEST(move_piece_in_place);
  RUN_TEST(jump_piece);
  RUN_TEST(jump_piece_backward);
  RUN_TEST(jump_piece_same_color);
  RUN_TEST(move_forward);
  RUN_TEST(kingmaking);

  GREATEST_MAIN_END();
}
