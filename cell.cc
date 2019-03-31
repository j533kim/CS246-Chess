#include "cell.h"

using namespace std;

Cell::Cell(shared_ptr<Piece> piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<State> &whoFrom) {
	if (whoFrom.getPiece()->getColor() == Color::White) {
		if (canmove(whoFrom.getName(), whoFrom.getRow(), whoFrom.getCol(), row, col)) {
			if (getState().W == Danger::No) setState({Danger::No, Danger::Yes});
			else setState({Danger::Yes,Danger::Yes});
		}
	} else if (whoFrom.getPiece()->getColor() == Color::Black) {
		if (canmove(whoFrom.getName(), whoFrom.getRow(), whoFrom.getCol(), row, col)) {
			if (getState().B == Danger::No) setState({Danger::Yes, Danger::No});
			else setState({Danger::Yes,Danger::Yes});
		}
	} else { // Color::NoColor
		State original = getState();
		int n = observers.size();
		if (original == {Danger::No, Danger::No}) return;
		else if (original.W == Danger::Yes) {
			for (int i = n - 63; i < n; ++i) {
				string name_ = observers.at(i).getPiece().getName();
				Color color_ = observers.at(i).getPiece().getColor();
				int row_ = observers.at(i).getRow();
				int col_ = observers.at(i).getCol();
				if (canmove(name_, row_, col_, row, col) && color_ == Color::Black) return;
			}
			setState({Danger::No, Danger::No});
		} else if (original.B == Danger::Yes) {
			for (int i = n - 63; i < n; ++i) {
				string name_ = observers.at(i).getPiece().getName();
				Color color_ = observers.at(i).getPiece().getColor();
				int row_ = observers.at(i).getRow();
				int col_ = observers.at(i).getCol();
				if (canmove(name_, row_, col_, row, col) && color_ == Color::White) return;
			}
			setState({Danger::No, Danger::No});
		}
	}
}

void Cell::placePiece(shared_ptr<Piece> piece) {
	this->piece = piece;
	notifyObservers();
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
		else this->piece = make_shared<Rook>(Color::Black, false);
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

shared_ptr<Piece> Cell::getPiece() const { return piece; }////////return pointer?

void Cell::setPiece(shared_ptr<Piece> piece) {
	this->piece = piece;
	notifyObservers();
}

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

//Cell::~Cell() { delete piece; }
