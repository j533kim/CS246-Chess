#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "board.h"


using namespace std;

////////////helper functions/////////////////

bool check_pos(int row_0, int col_0, int row_f, int col_f) {
	if (row_0 < 0 || row_0 > 7) return false;
	if (col_0 < 0 || col_0 > 7) return false;
	if (row_f < 0 || row_f > 7) return false;
	if (col_f < 0 || col_f > 7) return false;
	return true;
}

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
	if (!("a" <= pos.substr(0, 1) && pos.substr(0, 1) <= "h")) return false;
	if (!("1" <= pos.substr(1, 2) && pos.substr(1, 2) <= "8")) return false;
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
	if (theBoard.size() > 0) { // clear the old board
		theBoard.clear();
		delete td;
		delete ob;
	}
	td = new TextDisplay(); // new display
	ob = nullptr;
	for (int i = 0; i < 8; ++i) {
		vector<Cell> vect;
		theBoard.emplace_back(vect);
		for (int j = 0; j < 8; ++j) {
			theBoard.at(i).emplace_back(Cell(make_shared<NoPiece>(), i, j));
			theBoard.at(i).at(j).setState({Danger::No, Danger::No});
			theBoard.at(i).at(j).settheBoard(this);
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

void Board::removePiece(int row, int col, Move currMove) { 
	currMove.setLostPiece(theBoard.at(row).at(col).getPiece());
	theBoard.at(row).at(col).removePiece(); }

void Board::swapPiece(int row_0, int col_0, int row_f, int col_f) {
	shared_ptr<Piece> temp = theBoard.at(row_0).at(col_0).getPiece();
	theBoard.at(row_0).at(col_0).setPiece(theBoard.at(row_f).at(col_f).getPiece());
	theBoard.at(row_f).at(col_f).setPiece(temp);
}

void Board::move(string pos_in, string pos_fi, bool white_turn) { // 
	if ((!valid_pos(pos_in)) || (!valid_pos(pos_fi)) || pos_in == pos_fi) {
		throw InvalidMove();
		return;
	}
	int row_0 = row_return(pos_in);
	int col_0 = col_return(pos_in);
	int row_f = row_return(pos_fi);
	int col_f = col_return(pos_fi);
	Move currMove{{row_0,col_0}, {row_f, col_f}, nullptr, nullptr, true}; // currMove for initial to final
	Color moving_color = theBoard.at(row_0).at(col_0).getPiece()->getColor();
	if ((moving_color == Color::White && white_turn == 0) 
	|| (moving_color == Color::Black && white_turn == 1)) {
		throw InvalidMove();
		return;
	}
	Color dest_color = theBoard.at(row_f).at(col_f).getPiece()->getColor();
	if (moving_color == Color::Black && white_turn) {
		throw InvalidMove();
		return;
	}
	if ((moving_color == Color::NoColor) || (moving_color == dest_color)) {
		throw InvalidMove();
		return;
	}
	string name_ = theBoard.at(row_0).at(col_0).getPiece()->getName();
	if (!canmove(name_, row_0, col_0, row_f, col_f)) { 
	// the corresponding piece is not movable to the given final position
		throw InvalidMove();
		return;
	}
	bool en_passant = 0;
	if (theBoard.at(row_0).at(col_0).getPiece()->getName() == "pawn") {
		Color enemy_color = theBoard.at(row_0).at(col_f).getPiece()->getColor();
		bool twice_before = theBoard.at(row_0).at(col_f).getPiece()->getmovedTwoStepsBefore();
		if (row_0 + 1 == row_f && moving_color == Color::Black) {
			if (col_0 - 1 == col_f) {
				if (enemy_color == Color::White) {
					if (twice_before) {
						en_passant = 1;
					}
				}
			} else if (col_0 + 1 == col_f) {
				if (enemy_color == Color::White) {
					if (twice_before) {
						en_passant = 1;
					}
				}
			}
		} else if (row_0 - 1 == row_f && moving_color == Color::White) {
			if (col_0 - 1 == col_f) {
				if (enemy_color == Color::Black) {
					if (twice_before) {
						en_passant = 1;
					}
				}
			} else if (col_0 + 1 == col_f) {
				if (enemy_color == Color::Black) {
					if (twice_before) {
						en_passant = 1;
					}
				}
			}
		}
	}

	bool castle = false;
	if (theBoard.at(row_0).at(col_0).getPiece()->getName() == "king") {
		if (row_0 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) castle = true;
	}


	if (!castle) {    // en_passant and rest of the moves comes under this. // 
		removePiece(row_f, col_f,currMove);
		swapPiece(row_0, col_0, row_f, col_f);
		pastMoves.push_back(currMove);
	}

	// castling movement //////
	if (castle) {
		Move nextCurrMove;
		if (row_0 == 7 && col_0 == 4 && col_f == 2) { // white king to the left
			nextCurrMove.setStart({7,0});
			removePiece(7, 0,nextCurrMove); // rook removed
			removePiece(row_0, col_0,currMove);  // king being removed
			theBoard.at(7).at(2).setPiece(make_shared<King>(Color::White, false));
			theBoard.at(7).at(3).setPiece(make_shared<Rook>(Color::White, false));
			nextCurrMove.setEnd({7,3});
			pastMoves.push_back(nextCurrMove);
		} else if (row_0 == 7 && col_0 == 4 && col_f == 6) { // white king to the right
			nextCurrMove.setStart({7,7});
			removePiece(7, 7,nextCurrMove);
			removePiece(row_0, col_0,nextCurrMove);
			theBoard.at(7).at(6).setPiece(make_shared<King>(Color::White, false));
			theBoard.at(7).at(5).setPiece(make_shared<Rook>(Color::White, false));
			nextCurrMove.setEnd({7,5});
			pastMoves.push_back(nextCurrMove);
		} else if (row_0 == 0 && col_0 == 4 && col_f == 2) { // black king to the left
			nextCurrMove.setStart({0,0});
			removePiece(0, 0,nextCurrMove);
			removePiece(row_0, col_0,currMove);
			theBoard.at(0).at(2).setPiece(make_shared<King>(Color::Black, false));
			theBoard.at(0).at(3).setPiece(make_shared<Rook>(Color::Black, false));
			nextCurrMove.setEnd({0,3});
			pastMoves.push_back(nextCurrMove);
		} else {											// black king to the right 
			nextCurrMove.setStart({0,7});
			removePiece(0, 7, nextCurrMove);
			removePiece(row_0, col_0,currMove);
			theBoard.at(0).at(6).setPiece(make_shared<King>(Color::Black, false));
			theBoard.at(0).at(5).setPiece(make_shared<Rook>(Color::Black, false));
			nextCurrMove.setEnd({0,5});
			pastMoves.push_back(nextCurrMove);
		}
	}
	////////////////////////////////////////

	// movement for en_passant /////////
	if (en_passant) {
		Move nextCurrMove;
		if (theBoard.at(row_f).at(col_f).getPiece()->getColor() == Color::White) {
			nextCurrMove.setStart({row_f + 1, col_f});
			nextCurrMove.setEnd({row_f+1, col_f});
			removePiece(row_f + 1, col_f,nextCurrMove);   // ??
			nextCurrMove.setOfficialMove(false);
			pastMoves.push_back(nextCurrMove);
		} else { // black killing white
			nextCurrMove.setStart({row_f - 1, col_f});
			nextCurrMove.setEnd({row_f - 1, col_f});
			removePiece(row_f - 1, col_f,nextCurrMove);   // ??
			nextCurrMove.setOfficialMove(false);
			pastMoves.push_back(nextCurrMove);

		}
	}
	///////////////////////////////////

	// cancelling all the getmoved for other pieces
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
			if (curr->getmovedTwoStepsBefore()) {
				curr->setmovedTwoStepsBefore();
			}
		}
	}
	/////////////////////////

	// and setting the most recent pawn twice move
	if (theBoard.at(row_f).at(col_f).getPiece()->getName() == "pawn") {
		theBoard.at(row_f).at(col_f).getPiece()->settwoStepChance();
		if (row_0 - 2 == row_f || row_0 + 2 == row_f) theBoard.at(row_f).at(col_f).getPiece()->setmovedTwoStepsBefore();
	}
	/////////////////////////

	// upgrading pawns if necessary
	if (theBoard.at(row_f).at(col_f).getPiece()->getName() == "pawn") {
		shared_ptr<Piece> pawn = theBoard.at(row_f).at(col_f).getPiece();
		Move nextCurrMove{{row_f,col_f},{row_f,col_f},pawn,nullptr,false};   // make sure that this line is placed at the right position //
		if (theBoard.at(row_f).at(col_f).getPiece()->getColor() == Color::White) {
			if (row_f == 0) {
				shared_ptr<Piece> queen = make_shared<Queen>(Color::White);
				theBoard.at(row_f).at(col_f).setPiece(queen); 
				theBoard.at(row_f).at(col_f).getPiece()->setpawnPromotion(true);
				nextCurrMove.setAddedPiece(queen);
			}
		} else {
			if (row_f == 7) {
				shared_ptr<Piece> queen = make_shared<Queen>(Color::Black);
				theBoard.at(row_f).at(col_f).setPiece(queen);
				theBoard.at(row_f).at(col_f).getPiece()->setpawnPromotion(true);
				nextCurrMove.setAddedPiece(queen);
			}
		}
		pastMoves.push_back(nextCurrMove);
	}
	////////////////////////////

	// checking for stalemate /////////////
	int w_bishop = 0; // stalemate if not enough pieces for checkmate
	int b_bishop = 0;
	int w_knight = 0;
	int b_knight = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
			if (curr->getName() == "queen") return;
			if (curr->getName() == "rook") return;
			if (curr->getName() == "pawn") return;
			if (curr->getName() == "bishop") {
				if (curr->getColor() == Color::White) ++w_bishop;
				else ++b_bishop;
			}
			if (curr->getName() == "knight") {
				if (curr->getColor() == Color::White) ++w_knight;
				else ++b_knight;
			}
		}
	}
	if (w_bishop + w_knight > 1 || b_bishop + b_knight > 1) return;

	int row_w_king = 0;
	int col_w_king = 0;
	int row_b_king = 0;
	int col_b_king = 0;
	int other_pieces_w = 0;
	int other_pieces_b = 0;
	if (!getwhite_check()) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
				if (!(curr->getName() == "king" || curr->getName() == "nopiece")) {
					if (curr->getColor() == Color::White) ++other_pieces_w;
				} else if (curr->getName() == "king") {
					row_w_king = i;
					col_w_king = j;
				}
			}
		}
		if (canmove("king", row_w_king, col_w_king, row_w_king + 1, col_w_king + 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king, col_w_king + 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king - 1, col_w_king + 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king + 1, col_w_king - 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king, col_w_king - 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king - 1, col_w_king - 1)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king + 1, col_w_king)) return;
		if (canmove("king", row_w_king, col_w_king, row_w_king - 1, col_w_king)) return;
		setStalemate();
		return;
	} else if (!getblack_check()) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
				if (!(curr->getName() == "king" || curr->getName() == "nopiece")) {
					if (curr->getColor() == Color::Black) ++other_pieces_b;
				} else if (curr->getName() == "king") {
					row_b_king = i;
					col_b_king = j;
				}
			}
		}
		if (canmove("king", row_b_king, col_b_king, row_b_king + 1, col_b_king + 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king, col_b_king + 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king - 1, col_b_king + 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king + 1, col_b_king - 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king, col_b_king - 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king - 1, col_b_king - 1)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king + 1, col_b_king)) return;
		if (canmove("king", row_b_king, col_b_king, row_b_king - 1, col_b_king)) return;
		setStalemate();
		return;
	}
	////////////////////////
}

Color Board::winner() {
	if (getwhite_checkmate()) return Color::Black;
	else if (getblack_checkmate()) return Color::White;
	else return Color::NoColor;
}

bool Board::gameEnd() {
	if (getwhite_checkmate() || getblack_checkmate() || getStalemate()) return true;
	return false;
}

bool Board::setup_valid() { // called in the setup mode ONLY // 
	// perfect
	int white_king = 0;
	int black_king = 0;
	for (int i = 0; i < 8; ++i) { // checks if pawn exists in first/last row
		if (theBoard.at(0).at(i).getPiece()->getName() == "pawn") return false;
		if (theBoard.at(7).at(i).getPiece()->getName() == "pawn") return false;
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
			if (curr->getName() == "king") {
				if (curr->getCheck() == true) return false; // king is in check
				if (curr->getColor() == Color::Black) ++black_king;
				if (curr->getColor() == Color::White) ++white_king;
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
	placePiece_setup("N", "b1");
	placePiece_setup("B", "c1");
	placePiece_setup("Q", "d1");
	placePiece_setup("K", "e1");
	placePiece_setup("B", "f1");
	placePiece_setup("N", "g1");
	placePiece_setup("R", "h1");

	placePiece_setup("r", "a8"); // Black others
	placePiece_setup("n", "b8");
	placePiece_setup("b", "c8");
	placePiece_setup("q", "d8");
	placePiece_setup("k", "e8");
	placePiece_setup("b", "f8");
	placePiece_setup("n", "g8");
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
	} catch (InvalidMove In) {
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

std::vector<std::vector<Cell>> &Board::get_theBoard() { return theBoard; }

bool Board::getwhite_checkmate() const { return white_checkmate; }

bool Board::getblack_checkmate() const { return black_checkmate; }

bool Board::getStalemate() const { return stalemate; }

bool Board::getwhite_check() const { return white_check; }

bool Board::getblack_check() const { return black_check; }

void Board::setwhite_checkmate() { white_checkmate = true; }

void Board::setblack_checkmate() { black_checkmate = true; }

void Board::setStalemate() { stalemate = true; }

void Board::setwhite_check(bool check) { white_check = check; }

void Board::setblack_check(bool check) { black_check = check; }

ostream &operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}

// canmove function has to cover only the movement because (whether there is
// an ally's piece at the destination has been covered in move function)
// but still need to verify whether a piece (any piece) is on its way (blocking)
bool Board::canmove(string name, int row_0, int col_0, int row_f, int col_f) {
	if (!check_pos(row_0, col_0, row_f, col_f)) return false;
	shared_ptr<Piece> piece_0 = theBoard.at(row_0).at(col_0).getPiece(); // initial piece
	shared_ptr<Piece> piece_f = theBoard.at(row_f).at(col_f).getPiece(); // 
	if (name == "pawn") {
		if (piece_0->getColor() == Color::White) {
			if (row_f + 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && theBoard.at(row_f + 1).at(col_f).getPiece()->getColor() == Color::NoColor && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f + 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f + 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::Black) {
				return true;
			} else if (row_0 == 3 && row_f == 2 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1 && theBoard.at(3).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				else if (col_f == col_0 + 1 && theBoard.at(3).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
			}
			return false;
		} else { // color is black
			if (row_f - 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && theBoard.at(row_f - 1).at(col_f).getPiece()->getColor() == Color::NoColor && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f - 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f - 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::White) {
				return true;
			} else if (row_0 == 4 && row_f == 5 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1 && theBoard.at(4).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				else if (col_f == col_0 + 1 && theBoard.at(4).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
			}
			return false;
		}
	} else if (name == "knight") {
		if (piece_f->getColor() == piece_0->getColor()) return false; // if there is an ally on final cell
		if (row_0 + 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 + 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		if (row_0 - 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 - 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		return false;
	} else if (name == "bishop") {
		if (piece_0->getColor() == piece_f->getColor()) return false;
		if (row_f - 1 == row_0 && col_f - 1 == col_0) return true;
		if (row_f - 1 == row_0 && col_f + 1 == col_0) return true;
		if (row_f + 1 == row_0 && col_f - 1 == col_0) return true;
		if (row_f + 1 == row_0 && col_f + 1 == col_0) return true;
		float delta_y = row_f - row_0;
		float delta_x = col_f - col_0;
		float allowed_1 = -1;
		float allowed_2 = 1;
		if ((delta_x * allowed_1 != delta_y) && (delta_x * allowed_2 != delta_y)) return false;
		for (int i = row_f, j = col_f; i > row_0 && j > col_0;i--,j--) {  // final position is south east
			if (theBoard.at(i-1).at(j-1).getPiece()->getColor() == Color::NoColor) {
				if (i-2 == row_0 && j-2 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i > row_0 && j < col_0;i--,j++) { // position is south west
			if (theBoard.at(i-1).at(j+1).getPiece()->getColor() == Color::NoColor) {
				if (i-2 == row_0 && j+2 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i < row_0 && j > col_0;i++,j--) { // position is north east 
			if (theBoard.at(i+1).at(j-1).getPiece()->getColor() == Color::NoColor) {
				if (i+2 == row_0 && j-2 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		for (int i = row_f, j = col_f; i < row_0 && j < col_0;i++,j++) { // position is north west 
			if (theBoard.at(i+1).at(j+1).getPiece()->getColor() == Color::NoColor) {
				if (i+2 == row_0 && j+2 == col_0) {
					return true;
				}
			} else {
				return false;
			}
		}
		return false;
	} else if (name == "rook") {
		if (piece_f->getColor() == piece_0->getColor()) return false; // if there is an ally on final cell
		if (col_0 != col_f && row_0 != row_f) return false; // not one the same x or y axis
		bool valid = 0;
		if (row_0 - 1 == row_f && col_0 == col_f) return true;
		if (row_0 + 1 == row_f && col_0 == col_f) return true;
		if (row_0 == row_f && col_0 - 1 == col_f) return true;
		if (row_0 == row_f && col_0 + 1 == col_f) return true;
		for (int i = row_0; i > row_f + 1 ; --i) {  // moving upwards
			if (!(theBoard.at(i - 1).at(col_f).getPiece()->getColor() == Color::NoColor)) {
		  		valid = 0;
		  		break;
		  	} else {
		  		valid = 1;
		  	}
		}
		for (int j = row_0; j < row_f - 1; ++j) { // moving downwards
		  	if (!(theBoard.at(j + 1).at(col_f).getPiece()->getColor() == Color::NoColor)) {
		  		valid = 0;
		  		break;
		  	} else valid = 1;
		}
		for (int k = col_0; k < col_f - 1; ++k) {  // moving rightwards
		  	if (!(theBoard.at(row_f).at(k + 1).getPiece()->getColor() == Color::NoColor)) {
		  		valid = 0;
		  		break;
		  	} else valid = 1;
		}
		for (int l = col_0; l > col_f + 1; --l) { // moving leftwards
		  	if (!(theBoard.at(row_f).at(l - 1).getPiece()->getColor() == Color::NoColor)) {
		  		valid = 0;
		  		break;
		  	} else valid = 1;
		}
		if (valid == 0) return false;
		else return true;
	} else if (name == "queen") {
		if (canmove("rook", row_0, col_0, row_f, col_f)
		 || canmove("bishop", row_0, col_0, row_f, col_f)) return true;
		return false;
	} else if (name == "king") {
      if (piece_0->getColor() == piece_f->getColor()) return false;
      if (piece_0->getColor() == Color::White) {
      	if (theBoard.at(row_f).at(col_f).getState().W == Danger::Yes) return false;
      }
      if (piece_0->getColor() == Color::Black) {
      	if (theBoard.at(row_f).at(col_f).getState().B == Danger::Yes) return false;
      }
      bool checked_ = theBoard.at(row_f).at(col_f).getPiece()->getCheck();
      if (checked_ == true) return false;
	  if (row_f - 1 == row_0 && col_f - 1 == col_0) return true;
	  if (row_f - 1 == row_0 && col_f + 1 == col_0) return true;
	  if (row_f + 1 == row_0 && col_f - 1 == col_0) return true;
	  if (row_f + 1 == row_0 && col_f + 1 == col_0) return true;
	  if (row_0 - 1 == row_f && col_0 == col_f) return true;
	  if (row_0 + 1 == row_f && col_0 == col_f) return true;
	  if (row_0 == row_f && col_0 - 1 == col_f) return true;
	  if (row_0 == row_f && col_0 + 1 == col_f) return true;
	  if (row_0 == row_f && (col_0 == col_f - 2 || col_0 == col_f + 2)) { //castling
	  	int col_m = (col_f + col_0) / 2;
	  	State mid_state = theBoard.at(row_0).at(col_m).getState();
	  	State ini_state = theBoard.at(row_0).at(col_0).getState();
	  	State fin_state = theBoard.at(row_0).at(col_f).getState();
	  	Danger y = Danger::Yes;
	  	if (mid_state.W == y) return false;
	  	if (ini_state.W == y) return false;
	  	if (fin_state.W == y) return false;
	  	if (row_0 == 7 && col_0 == 4 && col_f == 2) { // white king to the left
	  		for (int i = 0; i < 3; ++i) {
	  			if (theBoard.at(row_0).at(1 + i).getPiece()->getName() != "nopiece") {
	  				return false;
	  			}
	  		}
	  		if (theBoard.at(7).at(0).getPiece()->getName() != "rook") return false;
	  		if (!(piece_0->getCastle())) return false;
	  		if (!(theBoard.at(7).at(0).getPiece()->getCastle())) return false;
	  	} else if (row_0 == 7 && col_0 == 4 && col_f == 6) { // white king to the right
	  		for (int i = 0; i < 2; ++i) {
	  			if (theBoard.at(row_0).at(5 + i).getPiece()->getName() != "nopiece") {
	  				return false;
	  			}
	  		}
	  		if (theBoard.at(7).at(7).getPiece()->getName() != "rook") return false;
	  		if (!(piece_0->getCastle())) return false;
	  		if (!(theBoard.at(7).at(7).getPiece()->getCastle())) return false;
	  	} else if (row_0 == 0 && col_0 == 4 && col_f == 2) { // black king to the left
	  		for (int i = 0; i < 3; ++i) {
	  			if (theBoard.at(row_0).at(1 + i).getPiece()->getName() != "nopiece") {
	  				return false;
	  			}
	  		}
	  		if (theBoard.at(0).at(0).getPiece()->getName() != "rook") return false;
	  		if (!(piece_0->getCastle())) return false;
	  		if (!(theBoard.at(0).at(0).getPiece()->getCastle())) return false;
	  	} else if (row_0 == 0 && col_0 == 4 && col_f == 6) { // black king to the right
	  		for (int i = 0; i < 2; ++i) {
	  			if (theBoard.at(row_0).at(5 + i).getPiece()->getName() != "nopiece") {
	  				return false;
	  			}
	  		}
	  		if (theBoard.at(0).at(7).getPiece()->getName() != "rook") return false;
	  		if (!(piece_0->getCastle())) return false;
	  		if (!(theBoard.at(0).at(7).getPiece()->getCastle())) return false;
	  	}
	  	return true;
	  }
	  return false;
	}
	return false; // if a piece is nopiece
}


