#include "bishop.h"

using namespace std;

Bishop::Bishop(Color color): Piece{color, 3, "bishop"} {}

bool Bishop::getCheck() const { return false; }

bool Bishop::getCastle() const { return false; }

bool Bishop::gettwoStepChance() const { return false; }
	
bool Bishop::getmovedTwoStepsBefore() const { return false; }

bool Bishop::getUpgrade() const { return false; }

void Bishop::setUpgrade() { return; }

void Bishop::setCastle() { return; }

void Bishop::setCheck() { return; }

void Bishop::settwoStepChance() { return; }

void Bishop::setmovedTwoStepsBefore() { return; }

void Bishop::upgrade(shared_ptr<Piece> piece) { return; }
