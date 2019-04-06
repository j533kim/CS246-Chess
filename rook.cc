#include "rook.h"

using namespace std;

Rook::Rook(Color color, bool castlingPossible): Piece{color, 5, "rook"},
 castlingPossible{castlingPossible} {}



//bool Rook::getCheck() const { return false; }

bool Rook::getCastle() const { return castlingPossible; }

/*

bool Rook::gettwoStepChance() const { return false; }
	
bool Rook::getmovedTwoStepsBefore() const { return false; }

bool Rook::getUpgrade() const { return false; }

void Rook::setUpgrade() {}
*/

void Rook::setCastle() { 
	if (castlingPossible) {
		castlingPossible = false; 
	} else {
		castlingPossible = true;
	}
}

/*

void Rook::setCheck() {}

void Rook::settwoStepChance() {}

void Rook::setmovedTwoStepsBefore() {}

void Rook::upgrade(shared_ptr<Piece> piece) {}
*/
