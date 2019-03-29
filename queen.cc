#include "queen.h"

using namespace std;

Queen::Queen(Color color): Piece{color, 9, "queen"} {}

bool Queen::getCheck() const {}

bool Queen::getCastle() const {}

bool Queen::gettwoStepChance() const {}
	
bool Queen::getmovedTwoStepsBefore() const {}

bool Queen::getUpgrade() const {}

void Queen::setUpgrade() {}

void Queen::setCastle() {}

void Queen::setCheck() {}

void Queen::settwoStepChance() {}

void Queen::setmovedTwoStepsBefore() {}

void Queen::upgrade(Piece *piece) {}
