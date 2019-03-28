#include "rook.h"

using namespace std;

Rook::Rook(Color color, bool castlingPossible): Piece{color, 5, "rook"},
 castlingPossible{castlingPossible} {}

bool Rook::getCastle() { return castlingPossible; }

void Rook::setCastle() { castlingPossible = false; }
