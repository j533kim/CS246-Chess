#include "king.h"

using namespace std;

King::King(Color color, bool castlingPossible): Piece{color, 10, "king"}, castlingPossible{castlingPossible}, checked{false} {}
 // king should not be checked when first created

bool King::getCheck() const { return checked; }

bool King::getCastle() const { return castlingPossible; }

void King::setCastle() { 
	if (castlingPossible) {
		castlingPossible = false; 
	} else {
		castlingPossible = true;
	}
 }
// always from true to false

void King::setCheck(bool check) { checked = check; }
