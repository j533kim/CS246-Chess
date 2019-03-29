#ifndef _NOPIECE_H_
#define _NOPIECE_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"

class NoPiece : public Piece {
public:
	NoPiece();
	bool getCheck() const;
	bool getCastle() const;
	bool gettwoStepChance() const;
	bool getmovedTwoStepsBefore() const;
	bool getUpgrade() const;
	void setUpgrade();
	void setCastle();
	void setCheck();
	void settwoStepChance();
	void setmovedTwoStepsBefore();
	void upgrade(Piece *piece);
};

#endif
