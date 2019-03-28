#include "king.h"

void King::castle() {

}

bool King::getCheck() { return checked; }

void King::setCheck(bool check) { checked = check; }

bool King::getCastle() { return castlingPossible; }

void King::setCastle() { castlingPossible = false; }
// always from true to false

King::King(color color, bool castlingPossible): Piece{color, 10}, castlingPossible{castlingPossible}, checked{false} name{"king"} {} // king should not be checked when first created
