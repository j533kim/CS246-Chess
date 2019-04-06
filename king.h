#ifndef _KING_H_
#define _KING_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class King : public Piece {
	bool castlingPossible;
	bool checked;
public:
	King(Color color, bool castlingPossible);
	bool getCheck() const;
	bool getCastle() const;
	void setCastle();
	void setCheck(bool check);
};

#endif
