#include "cell.h"

using namespace std;

Cell::Cell(Piece piece, int row, int col): piece{piece}, row{row}, col{col} {}

void Cell::notify(Subject<Info, State> &whoFrom) {

}

void Cell::placePiece(Piece &piece) {

	notifyObservers();
}

void Cell::removePiece() {
	piece = NoPiece();
	notifyObservers();
}

void Cell::placePiece_setup(string piece) {
	if (piece == "K") this->piece = King(Color::White);
	if (piece == "k") this->piece = King(Color::Black);
	if (piece == "N") this->piece = Knight(Color::White);
	..
	.
	.
	.
	.
	.
	.
	notifyObservers();
}

Piece Cell::getPiece() { return piece; }
