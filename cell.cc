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
	piece = NoPiece();
	notifyObservers();
}

void Cell::placePiece_setup(string piece) {
	if ((this->piece).value != 0) {
		throw InvalidMove();
		return;
	}
	// we already checked that the piece is valid type of piece
	if (piece == "K") this->piece = King(Color::White);
	if (piece == "k") this->piece = King(Color::Black);
	if (piece == "N") this->piece = Knight(Color::White);
	if (piece == "n") this->piece = Knight(Color::Black);
	if (piece == "R") this->piece = Rook(Color::White);
	if (piece == "r") this->piece = Rook(Color::Black);
	if (piece == "B") this->piece = Bishop(Color::White);
	if (piece == "b") this->piece = Bishop(Color::Black);
	if (piece == "Q") this->piece = Queen(Color::White);
	if (piece == "q") this->piece = Queen(Color::Black);
	if (piece == "P") this->piece = Pawn(Color::White);
	if (piece == "p") this->piece = Pawn(Color::Black);
	notifyObservers();
}

Piece Cell::getPiece() { return piece; }
