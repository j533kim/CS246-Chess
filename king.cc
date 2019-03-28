#include "king.h"

using namespace std;

void King::castle() {
	return;
}

bool King::getCheck() const { return checked; }

void King::setCheck(bool check) { checked = check; }

bool King::getCastle() const { return castlingPossible; }

void King::setCastle() { castlingPossible = false; }
// always from true to false

King::King(color color, bool castlingPossible): Piece{color, 10, "king"},
 castlingPossible{castlingPossible}, checked{false} {}
 // king should not be checked when first created
