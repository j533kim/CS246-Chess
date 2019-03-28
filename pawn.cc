#include "pawn.h"

using namespace std;

Pawn::Pawn(Color color, bool readyToUpgrade, bool twoStepChance):
 Piece{color, 1, "pawn"}, readyToUpgrade{false}, twoStepChance{twoStepChance}
 movedTwoStepsBefore{false} {}
// pawn should not be ready to upgrade when first created

void Pawn::upgrade(Piece piece) {

}
	
bool Pawn::getUpgrade() { return readyToUpgrade; }
	
void Pawn::setUpgrade() { readyToUpgrade = true; }
// we set this field always from false to true, never from true to false

bool Pawn::gettwoStepChance() { return twoStepChance; }

void Pawn::settwoStepChance() { twoStepChance = false; }
// we set this field always from true to false, never from false to true

bool Pawn::getmovedTwoStepsBefore() { return movedTwoStepsBefore; }

void Pawn::setmovedTwoStepsBefore() {
	if (movedTwoStepsBefore) movedTwoStepsBefore = false;
	else movedTwoStepsBefore = true;
}
