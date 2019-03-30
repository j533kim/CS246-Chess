#include "cell.h"

using namespace std;

Cell::Cell(Piece *piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<State> &whoFrom) {
	
}

void Cell::placePiece(Piece *piece) {
	delete (this->piece);
	this->piece = piece;
	notifyObservers();
}

void Cell::removePiece() {
	delete piece;
	piece = new NoPiece();
	notifyObservers();
}

void Cell::placePiece_setup(string piece) { // just for SETUP and default settings of the game
	if ((this->piece)->getValue() != 0) { // no piece will have 0 value 
		throw InvalidMove();
		return;
	}
	delete this->piece;
	// we already checked that the piece is valid type of piece
	if (piece == "K") {
		if (getRow() == 7 && getCol() == 4) this->piece = new King(Color::White, true);
		else this->piece = new King(Color::White, false);
	}
	if (piece == "k") {
		if (getRow() == 0 && getCol() == 4) this->piece = new King(Color::Black, true);
		else this->piece = new King(Color::Black, false);
	}
	if (piece == "P") {
		if (getRow() == 6) this->piece = new Pawn(Color::White, true);
		else this->piece = new Pawn(Color::White, false);
	}
	if (piece == "p") {
		if (getRow() == 1) this->piece = new Pawn(Color::Black, true);
		else this->piece = new Pawn(Color::Black, false);
	}
	if (piece == "R") {
		if (getRow() == 7 && (getCol() == 0 || getCol() == 7)) this->piece = new Rook(Color::White, true);
		else this->piece = new Rook(Color::Black, false);
	}
	if (piece == "r") {
		if (getRow() == 0 && (getCol() == 0 || getCol() == 7)) this->piece = new Rook(Color::Black, true);
		else this->piece = new Rook(Color::Black, false);	
	}
	if (piece == "N") this->piece = new Knight(Color::White);
	if (piece == "n") this->piece = new Knight(Color::Black);
	if (piece == "Q") this->piece = new Queen(Color::White);
	if (piece == "q") this->piece = new Queen(Color::Black);
	if (piece == "B") this->piece = new Bishop(Color::White);
	if (piece == "b") this->piece = new Bishop(Color::Black);
	notifyObservers();
}

Piece *Cell::getPiece() const { return piece; }////////return pointer?

void Cell::setPiece(Piece *piece) {
	this->piece = piece;
}

int Cell::getRow() const { return row; }

int Cell::getCol() const { return col; }

Cell::~Cell() { delete piece; }
