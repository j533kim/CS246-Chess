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

void Board::setObserver(Observer<State> *ob) { this->ob = ob; }

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
			theBoard.at(i).emplace_back(Cell( new NoPiece(Color:NoColor,0), i, j));
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
		theBoard.at(row).at(col).placePiece(piece);  // placePiece on a cell
	} catch (InvalidMove in) {
		throw InvalidMove();
	}
}

void Board::removePiece(int row, int col) { theBoard.at(row).at(col).remove(); }

void Board::swapPiece(int row_0, int col_0, int row_f, int col_f) { // jiwook was high when he wrote this
	/// perfect
	Piece *temp = theBoard.at(row_0).at(col_0).piece;
	theBoard.at(row_0).at(col_0).piece = theBoard.at(row_f).at(col_f).piece;
	theBoard.at(row_f).at(col_f).piece = temp;
	temp = nullptr;
}

void Board::move(string pos_initial, string pos_final) { // 
	if (!(valid_pos(pos_initial))) {
		throw InvalidMove();
		return;
	}
	if (!(valid_pos(pos_final))) {
		throw InvalidMove();
		return;
	}
	if (pos_initial == pos_final) {
		throw InvalidMove();
		return;
	}
	int row_0 = row_return(pos_initial);
	int col_0 = col_return(pos_initial);
	int row_f = row_return(pos_final);
	int col_f = col_return(pos_final);
	Color moving_piece_color = theBoard.at(row_0).at(col_0).piece.getColor();
	Color destination_color = theBoard.at(row_f).at(col_f).piece.getColor();



	// now only the condition for not moving

	if ((moving_piece_color == Color::NoColor) || (moving_piece_color == destination_color)) {
		throw InvalidMove();
		return;
	}
	if (!canmove(theBoard.at(row_0).at(col_0).piece->name, row_0, col_0, row_f, col_f)) { // the corresponding piece is not movable to the given final position
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

bool Board::setup_valid() { // called in the setup mode ONLY // 
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

void Board::game_default_setting() { // initial setup of a gameboard // 
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

// canmove function has to cover only the movement because (whether there is
// an ally's piece at the destination has been covered in move function)
// but still need to verify whether a piece (any piece) is on its way (blocking)
bool Board::canmove(string name, int row_0, int col_0, int row_f, int col_f) {
	Cell *cell_0 = theBoard.at(row_0).at(col_0);  // inital cell
	Cell *cell_f = theBoard.at(row_f).at(col_f);  // final cell
	Piece *piece_0 = theBoard.at(row_0).at(col_0).getPiece(); // initial piece
	Piece *piece_f = theBoard.at(row_f).at(col_f).getPiece(); // 
	if (name == "pawn") {
		if (piece_0->getColor() == Color::White) {
			if (row_f + 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && theBoard.at(row_f + 1).at(col_f).getPiece().getColor() == Color::NoColor && piece_f->getColor() == Color::NoColor) {
				piece_0->settwoStepChance(); // the pawn cannot move two steps anymore // changes to false
				return true;
			} else if (row_f + 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				piece_0->settwoStepChance();
				return true;
			} else if (row_f + 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::Black) {
				piece_0->settwoStepChance();
				return true;
			} /*else if (row_i == 3 && theBoard.at(3).at(col_i - 1).getPiece().getName() == "pawn" &&
					   theBoard.at(3).at(col_i - 1).getPiece().getColor() == Color::Black
			 		   && col_f == col_i - 1 && theBoard.at(3).at(col_i - 1).getPiece().getmovedTwoStepsBefore()) { // en passant
				return true;
			}*/
			return false;
		} else { // color is black
			if (row_f - 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && theBoard.at(row_f - 1).at(col_f).getPiece().getColor() == Color::NoColor && piece_f->getColor() == Color::NoColor) {
				piece_0->settwoStepChance(); // the pawn cannot move two steps anymore
				return true;
			} else if (row_f - 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				piece_0->settwoStepChance();
				return true;
			} else if (row_f - 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::White) {
				piece_0->settwoStepChance();
				return true;
			}
			return false;
		}
	} else if (name = "knight") {
		if (piece_f->getColor() == piece_0->getColor()) return false; // if there is an ally on final cell
		if (row_0 + 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 + 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		if (row_0 - 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 - 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		return false;
	} else if (name = "bishop") {
		if (piece_0->getColor() == piece_f->getColor()) return false;
		if (row_f - 1 == row_0 && col_f - 1 == col_0) return true;
		if (row_f - 1 == row_0 && col_f + 1 == col_0) return true;
		if (row_f + 1 == row_0 && col_f - 1 == col_0) return true;
		if (row_f + 1 == row_0 && col_f + 1 == col_0) return true;
		for (int i = row_f, j = col_f; i > row_0 && j > col_0;i--,j--) {  // position is south east
			if (theBoard.at(i-1).at(j-1).getPiece().getColor() == Color::NoColor) {
				if (i-1 == row_0 && j-1 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i > row_0 && j < col_0;i--,j++) { // position is south west
			if (theBoard.at(i-1).at(j+1).getPiece().getColor() == Color::NoColor) {
				if (i-1 == row_0 && j+1 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i < row_0 && j > col_0;i++,j--) { // position is north east 
			if (theBoard.at(i+1).at(j-1).getPiece().getColor() == Color::NoColor) {
				if (i+1 == row_0 && j-1 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i < row_0 && j < col_0;i++,j++) { // position is north west 
			if (theBoard.at(i+1).at(j+1).getPiece().getColor() == Color::NoColor) {
				if (i+1 == row_0 && j+1 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		return false;
	} else if (name = "rook") {
		if (piece_f->getColor() == piece_0->getColor()) return false; // if there is an ally on final cell
		if (col_0 != col_f && row_0 != row_f) return false; // not one the same x or y axis
		int valid = 0;
		if (row_0 - 1 == row_f && col_0 == col_f) return true;
		if (row_0 + 1 == row_f && col_0 == col_f) return true;
		if (row_0 == row_f && col_0 - 1 == col_f) return true;
		if (row_0 == row_f && col_0 + 1 == col_f) return true;
		for (int i = row_0; i > row_f + 1 ; --i) {
		  if (!(theBoard.at(i - 1).at(col_f).getPiece().getColor() == Color::NoColor)) {
		  	valid = 0;
		  	break;
		  }
		  else {
		  	valid = 1;
		  }
		}
		for (int j = row_0; j < row_f - 1 && r; ++j) {
		  if (!(theBoard.at(j + 1).at(col_f).getPiece().getColor() == Color::NoColor)) {
		  	valid = 0;
		  	break;
		  }
		  else {
		  	valid = 1;
		  }
		}
		for (int k = col_0; k < col_f - 1; ++k) {
		  if (!(theBoard.at(row_f).at(k + 1).getPiece().getColor() == Color::NoColor)) {
		  	valid = 0;
		  	break;
		  }
		  else {
		  	valid = 1;
		  }
		}
		for (int l = col_0; l > col_f + 1; --l) {
		  if (!(theBoard.at(row_f + 1).at(l - 1).getPiece().getColor() == Color::NoColor)) {
		  	valid = 0;
		  	break;
		  }
		  else {
		  	valid = 1;
		  }
		}
		if (valid == 0) {
			return false;
		} else {
			return true;
		}		
	} else if (name = "queen") {
		if (canmove("bishop", int row_0, int col_0, int row_f, int col_f)
		 || canmove("rook", int row_0, int col_0, int row_f, int col_f)) return true;
		else return false;
	} else { // name == "king"

	}
	cell_0 = nullptr;
	cell_f = nullptr;
	piece_0 = nullptr;
	piece_f = nullptr;
}
