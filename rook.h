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
	Rook(Color color, bool castlingPossible): Piece{color, 5, "rook"}, castlingPossible{castlingPossible} {}
	bool getCastle() const;
	void setCastle();
};

#endif
