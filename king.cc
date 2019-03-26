#include "king.h"

void King::castle() {

}

bool King::getCheck() { return checked; }

void King::setCheck(bool check) { checked = check; }

bool King::getCastle() { return castlingPossible; }

void King::setCastle(bool castle) { castlingPossible = castle; }
