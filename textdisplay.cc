#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() {
	vector<char> vect_odd; // white colored cell first (just space)
	vector<char> vect_even;
	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			vect_even.emplace_back(' ');
			vect_odd.emplace_back('_');
		} else {
			vect_even.emplace_back('_');
			vect_odd.emplace_back(' ');
		}
	}
	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) theDisplay.emplace_back(vect_even);
		else theDisplay.emplace_back(vect_odd);
	}
}

void TextDisplay::notify(Subject<State> &whoNotified) {
	int row = whoNotified.getRow();
	int col = whoNotified.getCol();
	string name = whoNotified.getPiece()->getName();
	Color color = whoNotified.getPiece()->getColor();
	if (color == Color::White) {
		if (name == "king") theDisplay.at(row).at(col) = 'K';
		if (name == "queen") theDisplay.at(row).at(col) = 'Q';
		if (name == "knight") theDisplay.at(row).at(col) = 'N';
		if (name == "bishop") theDisplay.at(row).at(col) = 'B';
		if (name == "rook") theDisplay.at(row).at(col) = 'R';
		if (name == "pawn") theDisplay.at(row).at(col) = 'P'; // pawn
	} else if (color == Color::Black) {
		if (name == "king") theDisplay.at(row).at(col) = 'k';
		if (name == "queen") theDisplay.at(row).at(col) = 'q';
		if (name == "knight") theDisplay.at(row).at(col) = 'n';
		if (name == "bishop") theDisplay.at(row).at(col) = 'b';
		if (name == "rook") theDisplay.at(row).at(col) = 'r';
		if (name == "pawn") theDisplay.at(row).at(col) = 'p'; // pawn
	} else if (color == Color::NoColor) {
		if ((row + col) % 2 == 0) theDisplay.at(row).at(col) = ' ';
		else theDisplay.at(row).at(col) = '_';
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) out << td.theDisplay.at(i).at(j);
		out << endl;
	}
	return out;
}
