#include "cell.h"

using namespace std;

Cell::Cell(Piece piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<Info, State> &whoFrom) {
	
}

void Cell::placePiece(Piece &piece) {
	this->piece = piece;
	notifyObservers();
}

void Cell::removePiece() {
	delete piece;
	piece = new NoPiece();
	notifyObservers();
}

void Cell::placePiece_setup(string piece) {
	if ((this->piece).value != 0) {
		throw InvalidMove();
		return;
	}
	// we already checked that the piece is valid type of piece
	if (piece == "K") this->piece = new King(Color::White);
	if (piece == "k") this->piece = new King(Color::Black);
	if (piece == "N") this->piece = new Knight(Color::White);
	if (piece == "n") this->piece = new Knight(Color::Black);
	if (piece == "R") this->piece = new Rook(Color::White);
	if (piece == "r") this->piece = new Rook(Color::Black);
	if (piece == "B") this->piece = new Bishop(Color::White);
	if (piece == "b") this->piece = new Bishop(Color::Black);
	if (piece == "Q") this->piece = new Queen(Color::White);
	if (piece == "q") this->piece = new Queen(Color::Black);
	if (piece == "P") this->piece = new Pawn(Color::White);
	if (piece == "p") this->piece = new Pawn(Color::Black);
	notifyObservers();
}

Piece Cell::getPiece() { return piece; }

Cell::~Cell() { delete piece; }
