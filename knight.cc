#include "knight.h"

using namespace std;

Knight::Knight(Color color): Piece{color, 3, "knight"} {}

bool Knight::getCheck() const {}

bool Knight::getCastle() const {}

bool Knight::gettwoStepChance() const {}
	
bool Knight::getmovedTwoStepsBefore() const {}

bool Knight::getUpgrade() const {}

void Knight::setUpgrade() {}

void Knight::setCastle() {}

void Knight::setCheck() {}

void Knight::settwoStepChance() {}

void Knight::setmovedTwoStepsBefore() {}

void Knight::upgrade(Piece *piece) {}
