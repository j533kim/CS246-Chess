#include "nopiece.h"

using namespace std;

NoPiece::NoPiece(): Piece{Color::NoColor, 0, "nopiece"} {}

bool NoPiece::getCheck() const { return false; }

bool NoPiece::getCastle() const { return false; }

bool NoPiece::gettwoStepChance() const { return false; }
	
bool NoPiece::getmovedTwoStepsBefore() const { return false; }

bool NoPiece::getUpgrade() const { return false; }

void NoPiece::setUpgrade() {}

void NoPiece::setCastle() {}

void NoPiece::setCheck() {}

void NoPiece::settwoStepChance() {}

void NoPiece::setmovedTwoStepsBefore() {}

void NoPiece::upgrade(Piece *piece) {}
