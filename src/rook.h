#ifndef _ROOK_H_
#define _ROOK_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class Rook : public Piece {
	bool castlingPossible;
public:
	Rook(Color color, bool castlingPossible);
	bool getCastle() const;
	void setCastle();
};

#endif
