# Unity native plugin example

This project is an example of building a unity plugin with native code. The
source file `checker.c` is a (partial) implementation of a game of checkers (or
draughts). This is packaged with a C# wrapper so it can be easily used from
other C# code.

For more information about how it works and how to build a native plugin, see [this blog post](https://blog.bugsnag.com/building-native-plugins-for-unity-games).

## Building

Build the package using `make`. It depends on knowing the location of your Unity
installation, so change the `UNITY` property in the [Makefile](Makefile) if needed.

## Installing

Install the package into a Unity project by opening
`build/Checkers.unitypackage` after building.

## Using

The interface includes methods for creating a checkers game and moving pieces.

```cs
using Checkers;

// ...
// Create a new checkers game with the names of the players:
var game = new Game("Sue", "Bob");

// Move a piece from (x, y) to (x2, y2)
// The board's (0, 0) is in the top left corner
bool success = game.MovePiece(1, 2, 2, 3);
if (success) {
  // redraw pieces, etc
}

// Check number of pieces in play (move piece automatically removes jumped
// pieces)
Debug.Log("Number of pieces :" + game.NumberOfPiecesInPlay());
```

## Testing

To run the tests for `checker.c`, run `make test`
