#include <iostream>
#include <string>
#include <vector>
#include "board.h"

using namespace std;

bool valid_piece(string piece) { // returns true if such piece exists in Chess
	if (lowercase(piece) == "k") return true;
	if (lowercase(piece) == "q") return true;
	if (lowercase(piece) == "b") return true;
	if (lowercase(piece) == "n") return true;
	if (lowercase(piece) == "r") return true;
	if (lowercase(piece) == "p") return true;
	return false;
}

bool valid_pos(string pos) {
	if (pos.length() != 2) return false;
	if (!(("a" <= pos.substr(0, 1)) && (pos.substr(0, 1) <= "h"))) return false;
	if (!(("1" <= pos.substr(1, 2)) && (pos.substr(1, 2) <= "8"))) return false;
	return true;
}

// 1,2,3,4,5,6,7,8 --> 7,6,5,4,3,2,1,0 (different from ours)
int row_return(string pos) { return 8 - stoi(pos.substr(1, 2)); }

// a,b,c,d,e,f,g,h --> 0,1,2,3,4,5,6,7 (differrent from ours)
int col_return(string pos) { return pos[0] - 'a'; }

Board::~Board() {
	delete td;
	delete ob;
}

void Board::setObserver(Observer<Info, State> *ob) {

}

void Board::init() {
	theBoard.clear(); // clear the old board
	delete td;
	delete ob;
	td = new TextDisplay(); // new display
	ob = nullptr;
	for (int i = 0; i < 8; ++i) {
		vector<Cell> vect;
		theBoard.emplace_back(vect);
		for (int j = 0; j < 8; ++j) {
			theBoard.at(i).emplace_back(Cell(NoPiece(), i, j));
		}
	}
	for (int i = 0; i < 8; ++i) { // setting neighbours for all subjects
		for (int j = 0; j < 8; ++j) {
			theBoard.at(i).at(j).attach(td); // attaching textdisplay
			for (int i_ = 0; i_ < 8; ++i_) { // attaching cell observers to each
				for (int j_ = 0; j_ < 8; ++j_) {
					if (!((i == i_) && (j == j_))) {
						theBoard.at(i).at(j).attach(&(theBoard.at(i_).at(j_)));
					}
				}
			}
		}
	}
}

void Board::move(string pos_initial, string pos_final) {

}

void Board::remove(string pos) {

}

Color Board::winner() {

}

bool Board::gameEnd() {

}

bool Board::setup_valid() {

}

void Board::game_default_setting() {

}

void Board::placePiece(string piece, string pos) {
	if (!(valid_piece(piece) && valid_pos(pos))) throw InvalidMove(); // invalid
	else {
		int row = row_return(pos);
		int col = col_return(pos);
		theBoard.at(row).at(col).placePiece(piece);
	}
}

ostream &operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}
