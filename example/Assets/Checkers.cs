using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace Checkers {
  public class Game {
    private IntPtr game;
    public Game(string playerName1, string playerName2) {
      game = NativeInterface.game_init(playerName1, playerName2);
    }

    public bool MovePiece(int fromX, int fromY, int toX, int toY) {
      var checker = NativeInterface.game_find_piece(game, fromX, fromY);
      if (checker == null || checker == IntPtr.Zero) {
        return false;
      }
      return NativeInterface.game_move_piece(game, checker, toX, toY);
    }

    public int NumberOfPiecesInPlay() {
      return NativeInterface.game_pieces_in_play(game);
    }

    public int NumberOfPiecesInPlay(int playerIndex) {
      return NativeInterface.game_pieces_for_player(game, playerIndex);
    }

    ~Game() {
      NativeInterface.game_free(game);
    }
  }

  internal class NativeInterface {

    [DllImport("__Internal")]
    public static extern IntPtr game_init(string playerName1, string playerName2);

    [DllImport("__Internal")]
    public static extern void game_free(IntPtr game);

    [DllImport("__Internal")]
    public static extern IntPtr game_find_piece(IntPtr game, int x, int y);

    [DllImport("__Internal")]
    public static extern bool game_move_piece(IntPtr game, IntPtr checker, int x, int y);

    [DllImport("__Internal")]
    public static extern int game_pieces_in_play(IntPtr game);

    [DllImport("__Internal")]
    public static extern int game_pieces_for_player(IntPtr game, int playerIndex);
  }
}
