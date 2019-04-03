#include "knight.h"

using namespace std;

Knight::Knight(Color color): Piece{color, 3, "knight"} {}

bool Knight::getCheck() const { return false; }

bool Knight::getCastle() const { return false; }

bool Knight::gettwoStepChance() const { return false;}
	
bool Knight::getmovedTwoStepsBefore() const { return false; }

bool Knight::getUpgrade() const { return false; }

void Knight::setUpgrade() { return; }

void Knight::setCastle() { return; }

void Knight::setCheck() { return; }

void Knight::settwoStepChance() { return; }

void Knight::setmovedTwoStepsBefore() { return; }

void Knight::upgrade(shared_ptr<Piece> piece) { return; }
