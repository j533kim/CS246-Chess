#include "cell.h"

using namespace std;

Cell::Cell(shared_ptr<Piece> piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<State> &whoFrom) {
	if (whoFrom.getPiece()->getColor() == Color::White) {
		if (gettheBoard()->canmove(whoFrom.getPiece()->getName(), whoFrom.getRow(), whoFrom.getCol(), row, col)) {
			if (getState().W == Danger::No) {
				setState({Danger::No, Danger::Yes});  // cell's black_state gets set to danger //
			}
			else setState({Danger::Yes,Danger::Yes});
			//if (this->getPiece()->getName() == "king" && getPiece()->getColor() == Color::Black) {
			//	this->getPiece()->setCheck(true);
			//	theBoard->setblack_check(true);
			//}
		}
	} else if (whoFrom.getPiece()->getColor() == Color::Black) {
		if (gettheBoard()->canmove(whoFrom.getPiece()->getName(), whoFrom.getRow(), whoFrom.getCol(), row, col)) {
			if (getState().B == Danger::No) {
				setState({Danger::Yes, Danger::No}); // cell's white_state get set to danger //
			}
			else setState({Danger::Yes,Danger::Yes});
			//if (this->getPiece()->getName() == "king" && this->getPiece()->getColor() == Color::White) {
			//	this->getPiece()->setCheck(true);
			//	theBoard->setwhite_check(true);
				// when should board's value of check be updated ???
			//}
		}
	} else { // Color::NoColor
		State original = getState();
		int n = getObservers().size();
		if (original.W == Danger::No && original.B == Danger::No) {
			//if (this->getPiece()->getName() == "king" && this->getPiece()->getColor() == Color::White) {
			//	this->getPiece()->setCheck(false);
			//	theBoard->setwhite_check(false);
			//} else if (this->getPiece()->getName() == "king" && this->getPiece()->getColor() == Color::Black) {
			//	this->getPiece()->setCheck(false);
			//	theBoard->setblack_check(false);
			//}
			return;
		}
		if (original.W == Danger::Yes) {  
			for (int i = n - 63; i < n; ++i) {
				string name_ = getObservers().at(i)->getPiece()->getName();
				Color color_ = getObservers().at(i)->getPiece()->getColor();
				int row_ = getObservers().at(i)->getRow();
				int col_ = getObservers().at(i)->getCol();
				if (gettheBoard()->canmove(name_, row_, col_, row, col) && color_ == Color::Black) return;
			}
			Danger black_ = getState().B;
			setState({Danger::No, black_});
			//if (this->getPiece()->getName() == "king" && this->getPiece()->getColor() == Color::White) {
			//	this->getPiece()->setCheck(false);
			//	theBoard->setwhite_check(false);
			//}

		}
		if (original.B == Danger::Yes) {
			for (int i = n - 63; i < n; ++i) {
				string name_ = getObservers().at(i)->getPiece()->getName();
				Color color_ = getObservers().at(i)->getPiece()->getColor();
				int row_ = getObservers().at(i)->getRow();
				int col_ = getObservers().at(i)->getCol();
				if (gettheBoard()->canmove(name_, row_, col_, row, col) && color_ == Color::White) return;
			}
			Danger white_ = getState().W;
			setState({white_, Danger::No});
			//if (this->getPiece()->getName() == "king" && this->getPiece()->getColor() == Color::Black) {
			//	this->getPiece()->setCheck(false);
			//	theBoard->setblack_check(false);
			//}
		}
	}
}

void Cell::removePiece() {
	piece = make_shared<NoPiece>();
	notifyObservers();
}

void Cell::placePiece_setup(string piece) { // just for SETUP and default settings of the game
	if ((this->piece)->getName() != "nopiece") { // no piece will have 0 value 
		throw InvalidMove();
		return;
	}
	if (!(piece == "k" || piece == "K" || piece == "P" || piece == "p" || piece == "R" || piece == "r" || piece == "N" || piece == "n" || piece == "Q" || piece == "q" || piece == "B" || piece == "b")) {
		throw InvalidMove();
		return;
	}
	//delete this->piece;
	// we already checked that the piece is valid type of piece
	if (piece == "K") {
		if (getRow() == 7 && getCol() == 4) this->piece = make_shared<King>(Color::White, true);
		else this->piece = make_shared<King>(Color::White, false);
	}
	if (piece == "k") {
		if (getRow() == 0 && getCol() == 4) this->piece = make_shared<King>(Color::Black, true);
		else this->piece = make_shared<King>(Color::Black, false);
	}
	if (piece == "P") {
		if (getRow() == 6) this->piece = make_shared<Pawn>(Color::White, true);
		else this->piece = make_shared<Pawn>(Color::White, false);
	}
	if (piece == "p") {
		if (getRow() == 1) this->piece = make_shared<Pawn>(Color::Black, true);
		else this->piece = make_shared<Pawn>(Color::Black, false);
	}
	if (piece == "R") {
		if (getRow() == 7 && (getCol() == 0 || getCol() == 7)) this->piece = make_shared<Rook>(Color::White, true);
		else this->piece = make_shared<Rook>(Color::White, false);
	}
	if (piece == "r") {
		if (getRow() == 0 && (getCol() == 0 || getCol() == 7)) this->piece = make_shared<Rook>(Color::Black, true);
		else this->piece = make_shared<Rook>(Color::Black, false);	
	}
	if (piece == "N") this->piece = make_shared<Knight>(Color::White);
	if (piece == "n") this->piece = make_shared<Knight>(Color::Black);
	if (piece == "Q") this->piece = make_shared<Queen>(Color::White);
	if (piece == "q") this->piece = make_shared<Queen>(Color::Black);
	if (piece == "B") this->piece = make_shared<Bishop>(Color::White);
	if (piece == "b") this->piece = make_shared<Bishop>(Color::Black);
	notifyObservers();
}

shared_ptr<Piece> Cell::getPiece() const { return piece; }

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

void Cell::setPiece(shared_ptr<Piece> piece) {
	this->piece = piece;
	notifyObservers();
}

void Cell::settheBoard(Board *theBoard)  { this->theBoard = theBoard; }

Board *Cell::gettheBoard()  { return theBoard; }
