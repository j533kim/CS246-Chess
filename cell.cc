#include "cell.h"

using namespace std;

Cell::Cell(shared_ptr<Piece> piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<State> &whoFrom) {
}

void Cell::placePiece(shared_ptr<Piece> piece) {
	//delete (this->piece);
	this->piece = piece;
	notifyObservers();
}

void Cell::removePiece() {
	//delete piece;
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
}

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

//Cell::~Cell() { delete piece; }
