#include "rook.h"

Rook::Rook(Color color, bool castlingPossible): Piece{color, 5},
 castlingPossible{castlingPossible}, name{"rook"} {}

bool Rook::getCastle() { return castlingPossible; }

void Rook::setCastle() { castlingPossible = false; }
