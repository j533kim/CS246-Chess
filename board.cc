#include <iostream>
#include <string>
#include <vector>
#include "board.h"

using namespace std;

////////////helper functions/////////////////

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

void Board::setObserver(Observer<State> *ob) {

}
//////////////////////////////////////////////////

void Board::setObserver(Observer<Info, State> *ob) { this->ob = ob; }

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

void Board::placePiece(Piece &piece, int row, int col) {
	try {
		theBoard.at(row).at(col).placePiece(piece);
	} catch (InvalidMove in) {
		throw InvalidMove();
	}
}

void Board::removePiece(int row, int col) { theBoard.at(row).at(col).remove(); }

void Board::swapPiece(int row_0, int col_0, int row_f, int col_f) {
	/// perfect
	Piece *temp = theBoard.at(row_0).at(col_0).piece;
	Piece *initial = theBoard.at(row_f).at(col_f).piece;
	Piece *final = temp;
	temp = nullptr;
}

void Board::move(string pos_initial, string pos_final) {
	if (!(valid_pos(pos_initial))) return false;
	if (!(valid_pos(pos_final))) return false;
	int row_0 = row_return(pos_initial);
	int col_0 = col_return(pos_initial);
	int row_f = row_return(pos_final);
	int col_f = col_return(pos_final);
	Color moving_piece_color = theBoard.at(row_0).at(col_0).piece.getColor();
	Color destination_color = theBoard.at(row_f).at(col_f).piece.getColor();


	// more conditions required (under checkmate, own piece blocking the way)

	if ((moving_piece_color == Color::NoColor) || (moving_piece_color == destination_color)) {
		throw InvalidMove();
		return;
	}
	removePiece(row_f, col_f);
	swapPiece(row_0, col_0, row_f, col_f);
}

Color Board::winner() {

}

bool Board::gameEnd() {

}

bool Board::setup_valid() {
	// perfect
	int white_king = 0;
	int black_king = 0;
	for (int i = 0; i < 8; ++i) { // checks if pawn exists in first/last row
		if (theBoard.at(0).at(i).getPiece().getValue() == 1) return false;
		if (theBoard.at(7).at(i).getPiece().getValue() == 1) return false;
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (theBoard.at(i).at(j).getPiece().getValue() == 10) {
				if (theBoard.at(i).at(j).getPiece().getCheck() == 1) return false; // king is in check
				if (theBoard.at(i).at(j).getPiece().getColor() == Color::Black) ++black_king;
				else ++white_king;
			}
		}
	}
	if (white_king != 1) return false;
	if (black_king != 1) return false;
	return true;
}

void Board::game_default_setting() {
	//perfect
	placePiece_setup("P", "a2"); // White pawns
	placePiece_setup("P", "b2");
	placePiece_setup("P", "c2");
	placePiece_setup("P", "d2");
	placePiece_setup("P", "e2");
	placePiece_setup("P", "f2");
	placePiece_setup("P", "g2");
	placePiece_setup("P", "h2");

	placePiece_setup("p", "a7"); // Black pawns
	placePiece_setup("p", "b7");
	placePiece_setup("p", "c7");
	placePiece_setup("p", "d7");
	placePiece_setup("p", "e7");
	placePiece_setup("p", "f7");
	placePiece_setup("p", "g7");
	placePiece_setup("p", "h7");

	placePiece_setup("R", "a1"); // White others
	placePiece_setup("B", "b1");
	placePiece_setup("N", "c1");
	placePiece_setup("Q", "d1");
	placePiece_setup("K", "e1");
	placePiece_setup("N", "f1");
	placePiece_setup("B", "g1");
	placePiece_setup("R", "h1");

	placePiece_setup("r", "a8"); // Black others
	placePiece_setup("b", "b8");
	placePiece_setup("n", "c8");
	placePiece_setup("q", "d8");
	placePiece_setup("k", "e8");
	placePiece_setup("n", "f8");
	placePiece_setup("b", "g8");
	placePiece_setup("r", "h8");
}

void Board::placePiece_setup(string piece, string pos) {
	if (!(valid_piece(piece) && valid_pos(pos))) {
		throw InvalidMove();
		return;
	}
	int row = row_return(pos);
	int col = col_return(pos);
	try {
		theBoard.at(row).at(col).placePiece_setup(piece);
	} catch (InvalidMove in) {
		throw InvalidMove();
	}
}

void Board::removePiece_setup(string pos) {
	if (!(valid_pos(pos))) {
		throw InvalidMove();
		return;
	}
	int row = row_return(pos);
	int col = col_return(pos);
	theBoard.at(row).at(col).removePiece();
}


ostream &operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}
