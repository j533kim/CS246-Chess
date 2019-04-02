#include "pawn.h"

using namespace std;

Pawn::Pawn(Color color, bool twoStepChance):
 Piece{color, 1, "pawn"}, readyToUpgrade{false}, twoStepChance{twoStepChance},
 movedTwoStepsBefore{false} {}
// pawn should not be ready to upgrade when first created

bool Pawn::getCheck() const { return false; }

bool Pawn::getCastle() const { return false; }

bool Pawn::gettwoStepChance() const { return twoStepChance; }
	
bool Pawn::getmovedTwoStepsBefore() const { return movedTwoStepsBefore; }

bool Pawn::getUpgrade() const { return readyToUpgrade; }

void Pawn::setUpgrade() { readyToUpgrade = true; }
// we set this field always from false to true, never from true to false

void Pawn::setCastle() {}

void Pawn::setCheck() {}

void Pawn::settwoStepChance() { 
	if (twoStepChance) twoStepChance = false;
	else twoStepChance = true;
}
// we set this field always from true to false

void Pawn::setmovedTwoStepsBefore() {
	if (movedTwoStepsBefore) movedTwoStepsBefore = false;
	else movedTwoStepsBefore = true;
}

void Pawn::upgrade(shared_ptr<Piece> piece) {

}
