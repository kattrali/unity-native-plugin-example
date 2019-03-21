using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Checkers;

public class CheckersGame : MonoBehaviour {

  private Game game;

	void Start () {
    game = new Game("sue", "bob");

    Debug.Log("Number of pieces in play: " + game.NumberOfPiecesInPlay());

    // (x, y) starts at the top left corner
    bool success = game.MovePiece(1, 2, 2, 3);
    Debug.Log("Did the move succeed? " + success);
	}

	// Update is called once per frame
	void Update () {

	}
}
