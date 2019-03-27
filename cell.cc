#include "cell.h"

using namespace std;

Cell::Cell(Piece piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<Info, State> &whoFrom) {
	
}

void Cell::placePiece(Piece &piece) {
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
	if ((this->piece).value != 0) { // no piece will have 0 value 
		throw InvalidMove();
		return;
	}
	delete piece;
	// we already checked that the piece is valid type of piece
	if (piece == "K") this->piece = new King(Color::White, value???);
	if (piece == "k") this->piece = new King(Color::Black, value???);
	if (piece == "N") this->piece = new Knight(Color::White, value???);
	if (piece == "n") this->piece = new Knight(Color::Black, value???);
	if (piece == "R") this->piece = new Rook(Color::White, value???);
	if (piece == "r") this->piece = new Rook(Color::Black, value???);
	if (piece == "B") this->piece = new Bishop(Color::White, value???);
	if (piece == "b") this->piece = new Bishop(Color::Black, value???);
	if (piece == "Q") this->piece = new Queen(Color::White, value???);
	if (piece == "q") this->piece = new Queen(Color::Black, value???);
	if (piece == "P") this->piece = new Pawn(Color::White, value???);
	if (piece == "p") this->piece = new Pawn(Color::Black, value???);
	notifyObservers();
}

Piece Cell::getPiece() { return piece; }

Cell::~Cell() { delete piece; }
