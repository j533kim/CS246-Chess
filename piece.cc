#include "piece.h"

using namespace std;

Piece::Piece(Color color, int value, string name): 
color{color}, value{value}, name{name} {}


string Piece::getName() const { return name; }

bool Piece::attacked() {
	return true;
}

bool Piece::attacking() {
	return true;
}
