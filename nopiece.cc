#include "nopiece.h"

using namespace std;

NoPiece::NoPiece(): Piece{Color::NoColor, 0, "nopiece"} {}

bool NoPiece::getCheck() const {}

bool NoPiece::getCastle() const {}

bool NoPiece::gettwoStepChance() const {}
	
bool NoPiece::getmovedTwoStepsBefore() const {}

bool NoPiece::getUpgrade() const {}

void NoPiece::setUpgrade() {}

void NoPiece::setCastle() {}

void NoPiece::setCheck() {}

void NoPiece::settwoStepChance() {}

void NoPiece::setmovedTwoStepsBefore() {}

void NoPiece::upgrade(Piece *piece) {}
