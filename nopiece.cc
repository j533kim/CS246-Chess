#include "nopiece.h"

using namespace std;

NoPiece::NoPiece(): Piece{Color::NoColor, 0, "nopiece"} {}

bool NoPiece::getCheck() const { return false; }

bool NoPiece::getCastle() const { return false; }

bool NoPiece::gettwoStepChance() const { return false; }
	
bool NoPiece::getmovedTwoStepsBefore() const { return false; }

bool NoPiece::getUpgrade() const { return false; }

void NoPiece::setUpgrade() { return; }

void NoPiece::setCastle() { return; }

void NoPiece::setCheck() { return; }

void NoPiece::settwoStepChance() { return; }

void NoPiece::setmovedTwoStepsBefore() { return; }

void NoPiece::upgrade(shared_ptr<Piece> piece) { return; }
