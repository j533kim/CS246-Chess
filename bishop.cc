#include "bishop.h"

using namespace std;

Bishop::Bishop(Color color): Piece{color, 3, "bishop"} {}

bool Bishop::getCheck() const { return false; }

bool Bishop::getCastle() const { return false; }

bool Bishop::gettwoStepChance() const { return false; }
	
bool Bishop::getmovedTwoStepsBefore() const { return false; }

bool Bishop::getUpgrade() const { return false; }

void Bishop::setUpgrade() {}

void Bishop::setCastle() {}

void Bishop::setCheck() {}

void Bishop::settwoStepChance() {}

void Bishop::setmovedTwoStepsBefore() {}

void Bishop::upgrade(Piece *piece) {}
