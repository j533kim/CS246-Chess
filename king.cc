#include "king.h"

using namespace std;

King::King(Color color, bool castlingPossible): Piece{color, 10, "king"}, castlingPossible{castlingPossible}, checked{false} {}
 // king should not be checked when first created


bool King::getCheck() const { return checked; }

bool King::getCastle() const { return castlingPossible; }

bool King::gettwoStepChance() const { return false; }
	
bool King::getmovedTwoStepsBefore() const { return false; }

bool King::getUpgrade() const { return false; }

void King::setUpgrade() {}

void King::setCastle() { castlingPossible = false; }
// always from true to false

void King::setCheck(bool check) {
	//if (checked) checked = false;
	//else checked = true;
	checked = check;
}

void King::settwoStepChance() {}

void King::setmovedTwoStepsBefore() {}

void King::upgrade(shared_ptr<Piece> piece) {}
