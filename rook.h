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
	bool getCastle();
	void setCastle();
}

#endif
