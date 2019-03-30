#include "queen.h"

using namespace std;

Queen::Queen(Color color): Piece{color, 9, "queen"} {}

bool Queen::getCheck() const { return false; }

bool Queen::getCastle() const { return false; }

bool Queen::gettwoStepChance() const { return false; }
	
bool Queen::getmovedTwoStepsBefore() const { return false; }

bool Queen::getUpgrade() const { return false; }

void Queen::setUpgrade() {}

void Queen::setCastle() {}

void Queen::setCheck() {}

void Queen::settwoStepChance() {}

void Queen::setmovedTwoStepsBefore() {}

void Queen::upgrade(shared_ptr<Piece> piece) {}
