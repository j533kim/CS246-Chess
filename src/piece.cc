#include "piece.h"

using namespace std;

Piece::Piece(Color color, int value, string name): 
color{color}, value{value}, name{name} {}


string Piece::getName() const { return name; }

int Piece::getValue() const { return value; }

Color Piece::getColor() const { return color; }

bool Piece::getCheck() const {}

bool Piece::getCastle() const {}

bool Piece::gettwoStepChance() const {}

bool Piece::getmovedTwoStepsBefore() const {}

void Piece::setCastle() {}
	
void Piece::setCheck(bool check) {}

void Piece::settwoStepChance() {}

void Piece::setmovedTwoStepsBefore() {}
