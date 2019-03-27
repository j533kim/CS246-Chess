#ifndef _KING_H_
#define _KING_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class King : public Piece {
	bool castlingPossible;
	bool checked;
public:
	King(color color, int value, bool castlingPossible, bool checked): Piece{color, 10}, castlingPossible{castlingPossible}, checked{checked} {}
	void castle();
	bool getCheck();
	void setCheck(bool check);
	bool getCastle();
	void setCastle(bool castle);
};

#endif
