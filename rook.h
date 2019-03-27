#ifndef _ROOK_H_
#define _ROOK_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Rook : public Piece {
	bool castlingPossible;
public:
	Rook(Color color, int value, bool castlingPossible): Piece{color, value}, castlingPossible{castlingPossible} {}
	bool getCastle();
	void setCastle();
}

#endif
