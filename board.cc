#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "board.h"
#include <cstdlib>

using namespace std;

////////////helper functions/////////////////

bool check_pos(int row_0, int col_0, int row_f, int col_f) {
	if (row_0 < 0 || row_0 > 7) return false;
	if (col_0 < 0 || col_0 > 7) return false;
	if (row_f < 0 || row_f > 7) return false;
	if (col_f < 0 || col_f > 7) return false;
	return true;
}

bool check_row_col(int row, int col) {
	if (row < 0 || row > 7) return false;
	if (col < 0 || col > 7) return false;
	return true;
}

string posStr(int row, int col) {
	string part_1;
	string part_2;
	if (col == 0) part_1 = "a";
	if (col == 1) part_1 = "b";
	if (col == 2) part_1 = "c";
	if (col == 3) part_1 = "d";
	if (col == 4) part_1 = "e";
	if (col == 5) part_1 = "f";
	if (col == 6) part_1 = "g";
	if (col == 7) part_1 = "h";
	if (row == 0) part_2 = "8";
	if (row == 1) part_2 = "7";
	if (row == 2) part_2 = "6";
	if (row == 3) part_2 = "5";
	if (row == 4) part_2 = "4";
	if (row == 5) part_2 = "3";
	if (row == 6) part_2 = "2";
	if (row == 7) part_2 = "1";
	return part_1 + part_2;
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
		pastMoves.clear();
		if (td) delete td;
		if (ob) delete ob;
		white_checkmate = false;
		black_checkmate = false;
		stalemate = false;
		white_check = false;
		checkTest = false;
		checkmateTest = false;
		black_check = false;
	}
	td = new TextDisplay(); // new display
	setObserver(new GraphicsDisplay());
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
			theBoard.at(i).at(j).attach(ob); // attaching graphicsdisplay
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

void Board::removePiece(int row, int col, shared_ptr<Move> currMove) { 
	currMove->setLostPiece(theBoard.at(row).at(col).getPiece());
	theBoard.at(row).at(col).removePiece();
}

void Board::swapPiece(int row_0, int col_0, int row_f, int col_f) {
	shared_ptr<Piece> temp = theBoard.at(row_0).at(col_0).getPiece();
	theBoard.at(row_0).at(col_0).setPiece(theBoard.at(row_f).at(col_f).getPiece()); 
	theBoard.at(row_f).at(col_f).setPiece(temp);   // piece is put first on final position


}

void Board::setHumans(Color color, bool human_player) {
	if (color == Color::White) white_human = human_player;
	else if (color == Color::Black) black_human = human_player;
}

void Board::move(string pos_in, string pos_fi, bool white_turn) { // 
	if ((!valid_pos(pos_in)) || (!valid_pos(pos_fi)) || pos_in == pos_fi) {
		//cout << "It's an invalid move!" << endl;
		throw InvalidMove();
		return;
	}
	int row_0 = row_return(pos_in);
	int col_0 = col_return(pos_in);
	int row_f = row_return(pos_fi);
	int col_f = col_return(pos_fi);
	shared_ptr<Move> currMove = make_shared<Move>(row_0, col_0, row_f, col_f, nullptr, nullptr, true); // main move // START //
	Color moving_color = theBoard.at(row_0).at(col_0).getPiece()->getColor();
	if ((moving_color == Color::White && white_turn == 0) || (moving_color == Color::Black && white_turn == 1)) {
		cout << "It's not your turn!" << endl;
		throw InvalidMove();   // THROW INVALID MOVE //
		return;
	}
	Color dest_color = theBoard.at(row_f).at(col_f).getPiece()->getColor();
	if (moving_color == Color::Black && white_turn) {
		//cout << "you are trying to move black piece." << endl;
		throw InvalidMove();
		return;
	}
	if ((moving_color == Color::NoColor) || (moving_color == dest_color)) {

		throw InvalidMove();
		return;
	}
	string name_ = theBoard.at(row_0).at(col_0).getPiece()->getName();

///////   making moves to bring their own king out of check 

	


	if ((getwhite_check() && (getCheckTest() == false)) && white_turn) {  // white king is under check and the white player is making a move
		//cout << "white king is under check and the white player is making a move" << endl;
		setCheckTest(true);
		try {
			move(pos_in, pos_fi, white_turn);
		} catch (InvalidMove in) {
			setCheckTest(false);
			throw InvalidMove();
		}
		if (getwhite_check() == false){
			setCheckTest(false);
			return;
		} else {
			this->undo();
			if (getwhite_checkmate()) {   // when making a move
				return;
			}
			setCheckTest(false);
			throw InvalidMove();
			return;
		}
	}
	if ((getblack_check() && (getCheckTest() == false)) && (!white_turn)) {   // BLACK KING IS UNDER CHECK AND AND THE BLACK PLAYER IS MAKING A MOVE
		//cout << " BLACK KING IS UNDER CHECK AND AND THE BLACK PLAYER IS MAKING A MOVE" << endl;
		setCheckTest(true);
		try {
			move(pos_in, pos_fi, white_turn); 
		} catch (InvalidMove in) {  
			setCheckTest(false);
			throw InvalidMove();
		} 

		if (getblack_check() == false){
			setCheckTest(false);
			return;
		} else {
			this->undo(); //
			if (getblack_checkmate()) {
				return;
			}
			setCheckTest(false);
			throw InvalidMove();
			return;
		}
	}


/////////


	if ((!(getblack_check() || getwhite_check())) && (getCheckTest() == false)) { // when any of the kings move with none of them in check // 
		//cout << "enters if a move will put it's own king in check" << endl;
		setCheckTest(true);
		try {
			move(pos_in, pos_fi, white_turn); // error //
			//cout << "try is successful" << endl;
		} catch (InvalidMove in) {  
			//cout << "throw's an invalid move in to check if a move will put its own king in check" << endl;
			setCheckTest(false);
			throw InvalidMove();
		} 
		if (white_turn) {     //black's turn
			//cout << "inside white" << endl;
			if (getblack_check() == true){
				//cout << "on white's turn, black king has been put in check" << endl;
				//this->undo();
				setCheckTest(false);
				
				//throw InvalidMove();
				//return;  // shouldn't return because you wanna check for checkmate as welll 

			} else if (getwhite_check() == true) {
				// cout << "on white's turn, white king has been put in check" << endl;
				this->undo();
				setCheckTest(false);
				throw InvalidMove();
				return;
			}
		} else {
			//cout << "inside black" << endl;
			if (getwhite_check() == true) {
				//cout << "on black's turn, white king has been put in check" << endl;
				 //this->undo();
				setCheckTest(false);
				
				//throw InvalidMove();
				//return;
			} else if (getblack_check() == true){
				//cout << "on black's turn, black king has been put in check" << endl;
				this->undo();
				setCheckTest(false);
				throw InvalidMove();
				return;
			} 
		}
		//cout << "enters if a move will put it's own king in check end undo" << endl;
		this->undo(); // 
		setCheckTest(false);
	}

	if (!canmove(name_, row_0, col_0, row_f, col_f)) { 
		cout <<  "the corresponding piece is not movable to the given final position" << endl;
		//cout << "canmove function doesnt allow the movement of the pieces" << endl;
		//cout << "can move is throwing invalid throw" << endl;
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
		pastMoves.push_back(currMove);        // MAIN MOVE // END //
	}

	// castling movement //////
	if (castle) {

		shared_ptr<Move> nextCurrMove = make_shared<Move>();
		if (row_0 == 7 && col_0 == 4 && col_f == 2) { // white king to the left
			nextCurrMove->row_0 = 7;
			nextCurrMove->col_0 = 0; 
			removePiece(7, 0,nextCurrMove); // rook removed
			removePiece(row_0, col_0, currMove);  // king being removed
			theBoard.at(7).at(2).setPiece(make_shared<King>(Color::White, false));
			theBoard.at(7).at(3).setPiece(make_shared<Rook>(Color::White, false));
			nextCurrMove->row_f = 7;
			nextCurrMove->col_f = 3; 
			//nextCurrMove->setEnd(make_shared<row_col>(7,3));
		} else if (row_0 == 7 && col_0 == 4 && col_f == 6) { // white king to the right
			nextCurrMove->row_0 = 7;
			nextCurrMove->col_0 = 7; 
			//nextCurrMove->setStart(make_shared<row_col>(7,7));
			removePiece(7, 7,nextCurrMove);
			removePiece(row_0, col_0,nextCurrMove);
			theBoard.at(7).at(6).setPiece(make_shared<King>(Color::White, false));
			theBoard.at(7).at(5).setPiece(make_shared<Rook>(Color::White, false));
			nextCurrMove->row_f = 7;
			nextCurrMove->col_f = 5; 
			//nextCurrMove->setEnd(make_shared<row_col>(7,5));
		} else if (row_0 == 0 && col_0 == 4 && col_f == 2) { // black king to the left
			nextCurrMove->row_0 = 0;
			nextCurrMove->col_0 = 0; 
			//nextCurrMove->setStart(make_shared<row_col>(0,0));
			removePiece(0, 0,nextCurrMove);
			removePiece(row_0, col_0,currMove);
			theBoard.at(0).at(2).setPiece(make_shared<King>(Color::Black, false));
			theBoard.at(0).at(3).setPiece(make_shared<Rook>(Color::Black, false));
			nextCurrMove->row_f = 0;
			nextCurrMove->col_f = 3; 
			//nextCurrMove->setEnd(make_shared<row_col>(0,3));
		} else {											// black king to the right 
			nextCurrMove->row_0 = 0;
			nextCurrMove->col_0 = 7; 
			//nextCurrMove->setStart(make_shared<row_col>(0,7));
			removePiece(0, 7, nextCurrMove);
			removePiece(row_0, col_0,currMove);
			theBoard.at(0).at(6).setPiece(make_shared<King>(Color::Black, false));
			theBoard.at(0).at(5).setPiece(make_shared<Rook>(Color::Black, false));
			nextCurrMove->row_f = 0;
			nextCurrMove->col_f = 5; 
			//nextCurrMove->setEnd(make_shared<row_col>(0,5));
		}
		pastMoves.push_back(currMove);
		pastMoves.push_back(nextCurrMove);
		setPastCastle(true);
	}

	////////////////////////////////////////

	// movement for en_passant /////////
	if (en_passant) {
		shared_ptr<Move> nextCurrMove = make_shared<Move>();
		if (theBoard.at(row_f).at(col_f).getPiece()->getColor() == Color::White) {
			nextCurrMove->row_0 = row_f + 1;
			nextCurrMove->col_0 = col_f; 
			//nextCurrMove->setStart(make_shared<row_col>(row_f + 1, col_f));
			nextCurrMove->row_f = row_f + 1;
			nextCurrMove->col_f = col_f; 
			//nextCurrMove->setEnd(make_shared<row_col>(row_f+1, col_f));
			removePiece(row_f + 1, col_f, nextCurrMove);   // ??
			nextCurrMove->setOfficialMove(false);
		} else { // black killing white
			nextCurrMove->row_0 = row_f - 1;
			nextCurrMove->col_0 = col_f; 
			nextCurrMove->row_f = row_f - 1;
			nextCurrMove->col_f = col_f;
			//nextCurrMove->setStart(make_shared<row_col>(row_f - 1, col_f));
			//nextCurrMove->setEnd(make_shared<row_col>(row_f - 1, col_f));
			removePiece(row_f - 1, col_f, nextCurrMove);   // ??
			nextCurrMove->setOfficialMove(false);

		}
		pastMoves.push_back(nextCurrMove);
		setPastEmPassant(true);
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
		shared_ptr<Piece> pawn = theBoard.at(row_f).at(col_f).getPiece();  // pawn 
		shared_ptr<Move> nextCurrMove = make_shared<Move>(row_f,col_f,row_f,col_f,pawn,nullptr,false);   // make sure that this line is placed at the right position //
		if (!((white_human && white_turn) || (black_human && (!white_turn)))) { //computer //
			if (theBoard.at(row_f).at(col_f).getPiece()->getColor() == Color::White) {
				if (row_f == 0) {
					shared_ptr<Piece> queen = make_shared<Queen>(Color::White);
					theBoard.at(row_f).at(col_f).setPiece(queen); 
					theBoard.at(row_f).at(col_f).getPiece()->setpawnPromotion(true);
					nextCurrMove->setAddedPiece(queen);
					pastMoves.push_back(nextCurrMove);
				}
			} else {
				if (row_f == 7) {
					shared_ptr<Piece> queen = make_shared<Queen>(Color::Black);
					theBoard.at(row_f).at(col_f).setPiece(queen);
					theBoard.at(row_f).at(col_f).getPiece()->setpawnPromotion(true);
					nextCurrMove->setAddedPiece(queen);
					pastMoves.push_back(nextCurrMove);
				}
			}
		} else {    
			shared_ptr<Piece> promote;
			if (row_f == 0 || row_f == 7) {
				while (true) {
					string what_you_want;
					if (getCheckTest()) {
						cout << "which piece do you want your pawn to get promoted to?" << endl;
						cin >> what_you_want;
						setpastWhat_you_want(what_you_want);
					} else {
						what_you_want = getpastWhat_you_want();
					}
					if (theBoard.at(row_f).at(col_f).getPiece()->getColor() == Color::White) {
						if (row_f == 0) {
							if (what_you_want == "Q" || what_you_want == "q") {
								promote = make_shared<Queen>(Color::White);
								break;
							} else if (what_you_want == "n" || what_you_want == "N") {
								promote = make_shared<Knight>(Color::White);
								break;
							} else if (what_you_want == "r" || what_you_want == "R") {
								promote = make_shared<Rook>(Color::White, false);
								break;
							} else if (what_you_want == "b" || what_you_want == "B") {
								promote = make_shared<Bishop>(Color::White);
								break;
							}
						} 
					} else {
						if (row_f == 7) {
							if (what_you_want == "Q" || what_you_want == "q") {
								promote = make_shared<Queen>(Color::Black);
								break;
							} else if (what_you_want == "n" || what_you_want == "N") {
								promote = make_shared<Knight>(Color::Black);
								break;
							} else if (what_you_want == "r" || what_you_want == "R") {
								promote = make_shared<Rook>(Color::Black, false);
								break;
							} else if (what_you_want == "b" || what_you_want == "B") {
								promote = make_shared<Bishop>(Color::Black);
								break;
							}
						}
					}
				}
				theBoard.at(row_f).at(col_f).setPiece(promote); 
				theBoard.at(row_f).at(col_f).getPiece()->setpawnPromotion(true);
				nextCurrMove->setAddedPiece(promote);
				pastMoves.push_back(nextCurrMove);
			}
		}
	}

/// check code
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			shared_ptr<Piece> piece = theBoard.at(i).at(j).getPiece();
			if (piece->getName() == "king" && piece->getColor() == Color::Black) {
				if (theBoard.at(i).at(j).getState().B == Danger::No) {
					piece->setCheck(false);
					setblack_check(false);
					//cout << cell.getRow() << "," << cell.getCol() << endl;
				} else {
					//setCheckedKing(cell);
					//cout << "black goes in check" << endl;
					piece->setCheck(true);
					setblack_check(true);
				}
			} else if (piece->getName() == "king" && piece->getColor() == Color::White) {
				if (theBoard.at(i).at(j).getState().W == Danger::No) {
					piece->setCheck(false);
					setwhite_check(false);
				} else {
					//setCheckedKing(cell);
					//cout << "white goes in check" << endl;
					piece->setCheck(true);
					setwhite_check(true);
				}
			}
		}
	}

	if (getblack_check() && getwhite_check()) { // if both kings come under check , put the opponent's king in check//
		if (white_turn) {
			setblack_check(false);
		} else {
			setwhite_check(false);
		}
	}
	

//// check code //
//// checmate code //

	if (((getblack_check() || getwhite_check()) && (getCheckMateTest() == false)) && (getCheckTest() == false)) {
		//cout << "enters checkmate function right now" << endl;
		setCheckMateTest(true);
		bool isCheckMate = true;
		vector<shared_ptr<Piece>> Pieces;
		vector<vector<int>> Row_Col_Pieces;    
		int totalPieces = 0;                     
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc;
				if (getblack_check()) {  
					if (theBoard.at(i).at(j).getPiece()->getColor() == Color::Black) {
						Pieces.push_back(theBoard.at(i).at(j).getPiece()); 
						vc.push_back(i);
						vc.push_back(j);
						Row_Col_Pieces.push_back(vc);
						totalPieces += 1;
					}
				} else {
					if (theBoard.at(i).at(j).getPiece()->getColor() == Color::White) {
						//cout << theBoard.at(i).at(j).getPiece()->getName() << endl;
						Pieces.push_back(theBoard.at(i).at(j).getPiece()); 
						vc.push_back(i);
						//cout << i << ",";
						vc.push_back(j);
						//cout << j << endl;
						Row_Col_Pieces.push_back(vc);
						totalPieces += 1;
					}
				}

			}
		}
		vector<int> index_v;
		int king_index; // index of the king in the vector 
		for (int j = 0; j < totalPieces; ++j) {
			if (Pieces.at(j)->getValue() == 10) {
				king_index = j;
			}
		}
		int king_row = Row_Col_Pieces.at(king_index).at(0);
		int king_col = Row_Col_Pieces.at(king_index).at(1);

		for (int k = 0; k < totalPieces; ++k) {
			for (int l = 0; l < 8; ++l) {
				for (int m = 0; m < 8; ++m) {

					///////
					bool turn = white_turn;
					if (canmove(Pieces.at(k)->getName(), Row_Col_Pieces.at(k).at(0), Row_Col_Pieces.at(k).at(1), l, m)) {
						//cout << "can move" << endl;
						//cout << l << "," << m << endl;
						//if ((Row_Col_Pieces.at(k).at(0) != l) && (Row_Col_Pieces.at(k).at(1) != m)) {

							string pos_initial = posStr(Row_Col_Pieces.at(k).at(0), Row_Col_Pieces.at(k).at(1));
							string pos_final = posStr(l,m);

							if (getblack_check()) {   // black check
								//cout << "not here for white check" << endl;
								//cout << white_turn << endl;
								setCheckTest(true);
								try {

									if (turn) {
										turn = 0;
									}
									move(pos_initial, pos_final, turn); // error //
																		
									//cout << "try is successful" << endl;
								} catch (InvalidMove in) {  
									setCheckTest(false);
									//cout << "throw's an invalid move in black check" << endl;
									//throw InvalidMove();
								
									continue;
								} 
								//cout << getblack_check() << endl;
								if (getblack_check() == false){

									// store the move which turns get black check false // 
									//cout << "shouldn't be here if it's giving a black checkmate" << endl;
									isCheckMate = false;
									this->undo();

									setCheckTest(false);
									setCheckMateTest(false);
									return;
								} else {
									this->undo(); //
									setCheckTest(false);
									//setCheckMateTest(false);
									//throw InvalidMove();
									//return;
									continue;
								}
							} else if (getwhite_check()) {  // white check 


								setCheckTest(true);

								if (!turn) {
									turn = 1;
								}

								try {
									
									move(pos_initial, pos_final, turn);
									//cout << "try" << endl;
									//cout << Pieces.at(k)->getName() << endl;
									

								} catch (InvalidMove in) {
									setCheckTest(false);
									//cout << "invalid move" << endl;

									//if (Pieces.at(k)->getName() == "king") {
									//	cout << "invalid" << endl;
									//	if (l == 6 && m == 4) {
									//		cout << "shouldn't happen" << endl;
									//	}
									//}

									continue;
								}
								if (getwhite_check() == false){

									// store the move which turns white check false // 
									//cout << "shouldn't be here if it's giving a white checkmate" << endl;
									isCheckMate = false;
									this->undo();
									setCheckTest(false);
									setCheckMateTest(false);
									return;

								} else {
									this->undo();
									setCheckTest(false);
									//throw InvalidMove();
									//return;
									continue;
								}
							} else {
								//cout << "else for checkmate function" << endl;
							}
						//}
					}


					/// 
				}
			}
		}

		if (isCheckMate) {
			if (getblack_check()){
				setblack_checkmate(true);
			} else if (getwhite_check()) {
				setwhite_checkmate(true);
			}
		}
		setCheckMateTest(false);
		return;
	}
	
//// checkmate code //

	// checking for stalemate /////////////
	if (getCheckMateTest() == false && getCheckTest() == false) {
		setCheckMateTest(true);
		vector<shared_ptr<Piece>> Pieces;
		vector<vector<int>> Row_Col_Pieces;    // stores the row and col index for the pieces array    
		int totalpieces = 0;                     
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc;
				if (theBoard.at(i).at(j).getPiece()->getColor() != Color::NoColor) {
					Pieces.push_back(theBoard.at(i).at(j).getPiece()); 
					vc.push_back(i);
					vc.push_back(j);
					Row_Col_Pieces.push_back(vc);
					totalpieces += 1;
				}			
			}
		} 
		int kings = 0;
		if (totalpieces == 2) {
			for (int k = 0; k < totalpieces; ++k) {
				if (Pieces.at(k)->getValue() == 10) {
					kings += 1;
				}
			}
		}
		if (kings == 2 && totalpieces == 2) {
			setStalemate();
			return;
		}
	}
		/*
		//cout << "inside" << endl;
		for (int k = 0; k < totalpieces; ++k) {
			for (int l = 0; l < 8; ++l) {
				for (int m = 0; m < 8; ++m) {
					bool turn = white_turn;
					string pos_initial = posStr(Row_Col_Pieces.at(k).at(0), Row_Col_Pieces.at(k).at(1));
					string pos_final = posStr(l,m);
					if (!turn) {
						if (!turn) {
							turn = 1;
						}
						if (canmove(Pieces.at(k)->getName(), Row_Col_Pieces.at(k).at(0), Row_Col_Pieces.at(k).at(1), l, m) && Pieces.at(k)->getColor() == Color::White) {
							try {

								move(pos_initial, pos_final, turn);
								this->undo ();
								setCheckTest(false);
								setCheckMateTest(false);
								return; 
							} catch (InvalidMove in) {
								continue;
							}
						}
					} else {
						if (turn) {
							turn = 0;
						}
						if (canmove(Pieces.at(k)->getName(), Row_Col_Pieces.at(k).at(0), Row_Col_Pieces.at(k).at(1), l, m) && Pieces.at(k)->getColor() == Color::Black) {
							try {

								//cout << turn << endl;
								move(pos_initial, pos_final, turn);
								//cout << Pieces.at(k)->getName() << endl;
								//cout << "no" << endl << pos_initial << " " << pos_final << endl;
								setCheckTest(false);
								setCheckMateTest(false);
								this->undo ();
								return; 
							} catch (InvalidMove in) {
								continue;
							}
						}
					}
				}
			}
		}
		setStalemate();
		setCheckTest(false);
		setCheckMateTest(false);
	}
	*/
	
	
}

void Board::undo() {
	shared_ptr<Move> currMove;
	if (!pastMoves.empty()){
		currMove = pastMoves.back();
	} else {
		throw InvalidMove();
	}
	int row_0 = currMove->row_0;    
	int col_0 = currMove->col_0;
	int row_f = currMove->row_f;  
	int col_f = currMove->col_f;
	pastMoves.pop_back();
	if (theBoard.at(row_f).at(col_f).getPiece()->getName() == "pawn" && (abs(row_0-row_f) == 2 && (col_0 == col_f))) {
		theBoard.at(row_f).at(col_f).getPiece()->settwoStepChance();
		//cout << "pawn two step chance is working" << endl;
	}
	if (row_0 == row_f && col_0 == col_f) {    // add just the piece that was stored // not official move
		theBoard.at(row_f).at(col_f).setPiece(currMove->getLostPiece());
		currMove = pastMoves.back();
		pastMoves.pop_back();
		row_0 = currMove->row_0;    
		col_0 = currMove->col_0;
		row_f = currMove->row_f;  
		col_f = currMove->col_f;

		swapPiece(row_0,col_0,row_f,col_f);  // moves from final to initial // the opposite //

		//swapPiece(row_f,col_f,row_0,col_0);
		if (currMove->getLostPiece() != nullptr) {
			theBoard.at(row_f).at(col_f).setPiece(currMove->getLostPiece());

		}
		if (getPastEmPassant()) {
			setPastEmPassant(false);
		}

	} else if (getPastCastle()) {
		swapPiece(row_0,col_0,row_f,col_f);  // moves from final to initial // the opposite //
		theBoard.at(row_0).at(col_0).getPiece()->setCastle();
		cout << theBoard.at(row_0).at(col_0).getPiece()->getCastle() << endl;


		currMove = pastMoves.back();
		pastMoves.pop_back();

		row_0 = currMove->row_0;    
		col_0 = currMove->col_0;
		row_f = currMove->row_f;  
		col_f = currMove->col_f;
		swapPiece(row_0,col_0,row_f,col_f);  
		theBoard.at(row_0).at(col_0).getPiece()->setCastle();
		cout << theBoard.at(row_0).at(col_0).getPiece()->getCastle() << endl;


		setPastCastle(false);

	} else {
		swapPiece(row_0,col_0,row_f,col_f);  // moves from final to initial // the opposite //

		//swapPiece(row_f,col_f,row_0,col_0);
		if (currMove->getLostPiece() != nullptr) {
			theBoard.at(row_f).at(col_f).setPiece(currMove->getLostPiece());
		}

	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			shared_ptr<Piece> piece = theBoard.at(i).at(j).getPiece();
			if (piece->getName() == "king" && piece->getColor() == Color::Black) {
				if (theBoard.at(i).at(j).getState().B == Danger::No) {
					piece->setCheck(false);
					setblack_check(false);
					//cout << cell.getRow() << "," << cell.getCol() << endl;
				} else {
					//setCheckedKing(cell);
					piece->setCheck(true);
					setblack_check(true);
				}
			} else if (piece->getName() == "king" && piece->getColor() == Color::White) {
				if (theBoard.at(i).at(j).getState().W == Danger::No) {
					piece->setCheck(false);
					setwhite_check(false);
				} else {
					//setCheckedKing(cell);
					//cout << "white goes in check" << endl;
					piece->setCheck(true);
					setwhite_check(true);
				}
			}
		}
	}
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
	int white_other_pieces = 0; //
	int black_other_pieces = 0;
	int white_bishop_knight = 0;
	int black_bishop_knight = 0;
	for (int i = 0; i < 8; ++i) { // checks if pawn exists in first/last row
		if (theBoard.at(0).at(i).getPiece()->getName() == "pawn" ||
			theBoard.at(7).at(i).getPiece()->getName() == "pawn") {
			//cout << "A pawn cannot be at the end of first/last row" << endl;
			return false;
		}
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			shared_ptr<Piece> curr = theBoard.at(i).at(j).getPiece();
			if (curr->getName() == "king") {
				if (curr->getCheck() == true) { // king is in check
					//cout << "A King cannot be in check!" << endl;
					return false;
				}
				if (curr->getColor() == Color::Black) ++black_king;
				if (curr->getColor() == Color::White) ++white_king;
			} else if (curr->getName() == "bishop" || curr->getName() == "knight") {
				if (curr->getColor() == Color::White) ++white_bishop_knight;
				else ++black_bishop_knight;
			} else if (curr->getName() != "nopiece") {
				if (curr->getColor() == Color::White) ++white_other_pieces;
				else ++black_other_pieces;
			}
		}
	}
	if (white_other_pieces == 0 && black_other_pieces == 0) {
		if (white_bishop_knight < 2 && black_bishop_knight < 2) {
			//cout << "Put some more pieces, this game will automatically be a draw" << endl;
			return false;
		}
	}
	if (white_king != 1) {
		//cout << "Exactly one white king needed..." << endl;
		return false;
	}
	if (black_king != 1) {
		//cout << "Exactly one black king needed..." << endl;
		return false;
	}
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
		theBoard.at(row).at(col).placePiece_setup(piece);  /// 
	} catch (InvalidMove In) {
		throw InvalidMove();
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			shared_ptr<Piece> piece = theBoard.at(i).at(j).getPiece();
			if (piece->getName() == "king" && piece->getColor() == Color::Black) {
				if (theBoard.at(i).at(j).getState().B == Danger::No) {
					piece->setCheck(false);
					setblack_check(false);
					//cout << cell.getRow() << "," << cell.getCol() << endl;
				} else {
					//setCheckedKing(cell);
					cout << "black goes in check" << endl;
					piece->setCheck(true);
					setblack_check(true);
				}
			} else if (piece->getName() == "king" && piece->getColor() == Color::White) {
				if (theBoard.at(i).at(j).getState().W == Danger::No) {
					piece->setCheck(false);
					setwhite_check(false);
				} else {
					//setCheckedKing(cell);
					cout << "white goes in check" << endl;
					piece->setCheck(true);
					setwhite_check(true);
				}
			}
		}
	}
}

void Board::removePiece_setup(string pos) {
	if (!(valid_pos(pos))) {
		throw InvalidMove();
		return;
	}
	int row = row_return(pos);
	int col = col_return(pos);
	if (theBoard.at(row).at(col).getPiece()) {
		theBoard.at(row).at(col).removePiece();	
	}
}

std::vector<std::vector<Cell>> &Board::get_theBoard() { return theBoard; }

bool Board::getwhite_checkmate() const { return white_checkmate; }

bool Board::getblack_checkmate() const { return black_checkmate; }

bool Board::getStalemate() const { return stalemate; }

bool Board::getwhite_check() const { return white_check; }

bool Board::getblack_check() const { return black_check; }

void Board::setwhite_checkmate(bool check) { white_checkmate = check; }

void Board::setblack_checkmate(bool check) { black_checkmate = check; }

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
	//cout << "inside canmove" << endl;
	if (!check_pos(row_0, col_0, row_f, col_f)) return false;
	shared_ptr<Piece> piece_0 = theBoard.at(row_0).at(col_0).getPiece(); // initial piece
	shared_ptr<Piece> piece_f = theBoard.at(row_f).at(col_f).getPiece(); //
	if (piece_0->getColor() == piece_f->getColor()) return false;
	if (piece_0->getColor() == Color::NoColor) return false;
	if (name == "pawn") {
		if (piece_0->getColor() == Color::White) {
			if (row_f + 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && piece_f->getColor() == Color::NoColor) {
				if (theBoard.at(row_f + 1).at(col_f).getPiece()->getColor() == Color::NoColor) return true;
			} else if (row_f + 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f + 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::Black) {
				return true;
			} else if (row_0 == 3 && row_f == 2 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1) {
					if (theBoard.at(3).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
				else if (col_f == col_0 + 1) {
					if (theBoard.at(3).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
			}
			return false;
		} else if (piece_0->getColor() == Color::Black) { // color is black
			if (row_f - 2 == row_0 && col_0 == col_f && piece_0->gettwoStepChance() == true && piece_f->getColor() == Color::NoColor) {
				if (theBoard.at(row_f - 1).at(col_f).getPiece()->getColor() == Color::NoColor) return true;
			} else if (row_f - 1 == row_0 && col_0 == col_f && piece_f->getColor() == Color::NoColor) {
				return true;
			} else if (row_f - 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f) && piece_f->getColor() == Color::White) {
				return true;
			} else if (row_0 == 4 && row_f == 5 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1) {
					if (theBoard.at(4).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				} else if (col_f == col_0 + 1) {
					if (theBoard.at(4).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
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
		Danger y = Danger::Yes;
		if (piece_0->getColor() == piece_f->getColor()) return false;
      	State danger_ = theBoard.at(row_f).at(col_f).getState();
      	//if (piece_0->getColor() == Color::White && danger_.W == Danger::Yes)  return false;
      	//if (piece_0->getColor() == Color::Black && danger_.B == Danger::Yes)  return false;
    //  cout << "inside kign" << endl;
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
	 	 	if (theBoard.at(row_0).at(col_0).getPiece()->getColor() == Color::White) { //castling white
	 	 		if (mid_state.W == y) return false;
	  			if (ini_state.W == y) return false;
	  			if (fin_state.W == y) return false;
	 	 		if (row_0 == 7 && col_0 == 4 && col_f == 2) { // white king to the left
	  				for (int i = 0; i < 3; ++i) {
	  					if (theBoard.at(row_0).at(1 + i).getPiece()->getName() != "nopiece") return false;
	  				}
	  				if (theBoard.at(7).at(0).getPiece()->getName() != "rook") return false;
	  				if (!(piece_0->getCastle())) return false;
	  				if (!(theBoard.at(7).at(0).getPiece()->getCastle())) return false;
	  				return true;
	  			} else if (row_0 == 7 && col_0 == 4 && col_f == 6) { // white king to the right
	  				for (int i = 0; i < 1; ++i) {
	  					if (theBoard.at(row_0).at(5 + i).getPiece()->getName() != "nopiece") return false;
	  				}
	  				if (theBoard.at(7).at(7).getPiece()->getName() != "rook") return false;
	  				if (!(piece_0->getCastle())) return false;
	  				if (!(theBoard.at(7).at(7).getPiece()->getCastle())) return false;
	  				return true;
	  			}
	  		} else if (theBoard.at(row_0).at(col_0).getPiece()->getColor() == Color::Black) { //castling black
	  			if (mid_state.B == y) return false;
		  		if (ini_state.B == y) return false;
		  		if (fin_state.B == y) return false;
	  			if (row_0 == 0 && col_0 == 4 && col_f == 2) { // white king to the left
	  				for (int i = 0; i < 3; ++i) {
	  					if (theBoard.at(row_0).at(1 + i).getPiece()->getName() != "nopiece") return false;
	  				}
	  				if (theBoard.at(0).at(0).getPiece()->getName() != "rook") return false;
	  				if (!(piece_0->getCastle())) return false;
	  				if (!(theBoard.at(0).at(0).getPiece()->getCastle())) return false;
	  				return true;
	  			} else if (row_0 == 0 && col_0 == 4 && col_f == 6) { // white king to the right
	  				for (int i = 0; i < 1; ++i) {
	  					if (theBoard.at(row_0).at(5 + i).getPiece()->getName() != "nopiece") return false;
	  				}
	  				if (theBoard.at(0).at(7).getPiece()->getName() != "rook") return false;
	  				if (!(piece_0->getCastle())) return false;
	  				if (!(theBoard.at(0).at(7).getPiece()->getCastle())) return false;
	  				return true;
	  			}
	  		}
	  	return false;
	  }
	}
	return false;
}

bool Board::canAttack(string name, int row_0, int col_0, int row_f, int col_f) {
	//cout << "inside canmove" << endl;
	if (!check_pos(row_0, col_0, row_f, col_f)) return false;
	shared_ptr<Piece> piece_0 = theBoard.at(row_0).at(col_0).getPiece(); // initial piece
	shared_ptr<Piece> piece_f = theBoard.at(row_f).at(col_f).getPiece(); // 
	if (piece_0->getColor() == Color::NoColor) return false;
	if (name == "pawn") {
		if (piece_0->getColor() == Color::White) {
			if (row_f + 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				return true;
			} else if (row_0 == 3 && row_f == 2 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1) {
					if (theBoard.at(3).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
				else if (col_f == col_0 + 1) {
					if (theBoard.at(3).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(3).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
			}
			return false;
		} else if (piece_0->getColor() == Color::Black) { // color is black
			if (row_f - 1 == row_0 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				return true;
			} else if (row_0 == 4 && row_f == 5 && (col_0 - 1 == col_f || col_0 + 1 == col_f)) {
				if (col_f == col_0 - 1) {
					if (theBoard.at(4).at(col_0 - 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 - 1).getPiece()->getmovedTwoStepsBefore()) return true;
				} else if (col_f == col_0 + 1) {
					if (theBoard.at(4).at(col_0 + 1).getPiece()->getName() == "pawn" && theBoard.at(4).at(col_0 + 1).getPiece()->getmovedTwoStepsBefore()) return true;
				}
			}
			return false;
		}
	} else if (name == "knight") {
		if (row_0 + 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 + 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		if (row_0 - 1 == row_f && (col_0 - 2 == col_f || col_0 + 2 == col_f)) return true;
		if (row_0 - 2 == row_f && (col_0 - 1 == col_f || col_0 + 1 == col_f)) return true;
		return false;
	} else if (name == "bishop") {
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
		if (canAttack("rook", row_0, col_0, row_f, col_f)
		 || canAttack("bishop", row_0, col_0, row_f, col_f)) return true;
		return false;
	} else if (name == "king") {
		Danger y = Danger::Yes;
      	State danger_ = theBoard.at(row_f).at(col_f).getState();
	 	 if (row_f - 1 == row_0 && col_f - 1 == col_0) return true;
	 	 if (row_f - 1 == row_0 && col_f + 1 == col_0) return true;
	 	 if (row_f + 1 == row_0 && col_f - 1 == col_0) return true;
	 	 if (row_f + 1 == row_0 && col_f + 1 == col_0) return true;
	 	 if (row_0 - 1 == row_f && col_0 == col_f) return true;
	 	 if (row_0 + 1 == row_f && col_0 == col_f) return true;
	 	 if (row_0 == row_f && col_0 - 1 == col_f) return true;
	 	 if (row_0 == row_f && col_0 + 1 == col_f) return true;
	}
	return false;
}

void Board::printHistory(int turn) {
	int size = pastMoves.size();
	string tur = turn == 0 ?  "W" : "B" ;
	for (int i = size-1; i >= 0; i--) {
		if (pastMoves.at(i)->getOfficialMove()) {
			cout << tur << ": " << posStr(pastMoves.at(i)->row_0, pastMoves.at(i)->col_0) << " " << posStr(pastMoves.at(i)->row_f, pastMoves.at(i)->col_f) << endl;
			if (tur == "B") {
				tur = "W";
			} else {
				tur = "B";
			}
		}
	}
}
