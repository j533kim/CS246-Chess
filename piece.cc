#include "piece.h"

using namespace std;

Piece::Piece(Color color, int value, string name): 
color{color}, value{value}, name{name} {}


string Piece::getName() const { return name; }

int Piece::getValue() const { return value; }


// temp ////////////////////////////////
bool Piece::attacked() const {
	return true;
}

bool Piece::attacking() const {
	return true;
}
///////////////////////////////

Color Piece::getColor() const { return color; }

void Piece::upgrade(Piece *piece) {}

bool Piece::getCheck() const {}

bool Piece::getCastle() const {}

bool Piece::gettwoStepChance() const {}

bool Piece::getmovedTwoStepsBefore() const {}

bool Piece::getUpgrade() const {}

void Piece::setUpgrade() {}

void Piece::setCastle() {}
	
void Piece::setCheck() {}

void Piece::settwoStepChance() {}

void Piece::setmovedTwoStepsBefore() {}

