#ifndef _KING_H_
#define _KING_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"
#include "piece.h"

class King : public Piece {
	bool castlingPossible;
	bool checked;
public:
	King(Color color, bool castlingPossible);
	void castle();
	bool getCheck() const;
	void setCheck(bool check);
	bool getCastle() const;
	void setCastle();
};

#endif
