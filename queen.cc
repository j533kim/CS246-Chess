#include "queen.h"

using namespace std;

Queen::Queen(Color color): Piece{color, 9, "queen"}, pawnPromotion{false} {}

bool Queen::getCheck() const { return false; }

bool Queen::getCastle() const { return false; }

bool Queen::gettwoStepChance() const { return false; }
	
bool Queen::getmovedTwoStepsBefore() const { return false; }

bool Queen::getUpgrade() const { return false; }

void Queen::setUpgrade() {}

void Queen::setCastle() {}

void Queen::setCheck() {}

bool Queen::getpawnPromotion() const {
	return pawnPromotion;
}

bool Queen::setpawnPromotion(bool value) {
	pawnPromotion = value;
}

void Queen::settwoStepChance() {}

void Queen::setmovedTwoStepsBefore() {}

void Queen::upgrade(shared_ptr<Piece> piece) {}
