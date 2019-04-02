#ifndef _MOVE_
#define _MOVE_
#include "piece.h"


struct row_col{
	int row;
	int col;
}

class Move {
	row_col start;
	row_col final;
	Piece lostPiece;
}

