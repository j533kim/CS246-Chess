#include "piece.h"

using namespace std;

Piece::Piece(Color color, int value, string name): 
color{color}, value{value}, name{name} {}


string Piece::getName() const { return name; }

int Piece::getValue() const { return value; }

bool Piece::attacked() {
	return true;
}

bool Piece::attacking() {
	return true;
}

Color Piece::getColor() const { return color; }
