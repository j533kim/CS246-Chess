#include "rook.h"

using namespace std;

Rook::Rook(Color color, bool castlingPossible): Piece{color, 5, "rook"},
 castlingPossible{castlingPossible} {}

bool Rook::getCastle() const { return castlingPossible; }

void Rook::setCastle() { 
	if (castlingPossible) {
		castlingPossible = false; 
	} else {
		castlingPossible = true;
	}
}
