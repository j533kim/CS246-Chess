#include "bishop.h"

using namespace std;

Bishop::Bishop(Color color): Piece{color, 3, "bishop"} {}

bool Bishop::getCheck() const {}

bool Bishop::getCastle() const {}

bool Bishop::gettwoStepChance() const {}
	
bool Bishop::getmovedTwoStepsBefore() const {}

bool Bishop::getUpgrade() const {}

void Bishop::setUpgrade() {}

void Bishop::setCastle() {}

void Bishop::setCheck() {}

void Bishop::settwoStepChance() {}

void Bishop::setmovedTwoStepsBefore() {}

void Bishop::upgrade(Piece *piece) {}
