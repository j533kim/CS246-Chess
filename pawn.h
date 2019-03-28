#ifndef _PAWN_H_
#define _PAWN_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Pawn : public Piece {
	bool readyToUpgrade;
	bool twoStepChance;
	bool movedTwoStepsBefore; // for En Passant
public:
	Pawn(Color color, bool twoStepChance);
	void upgrade(Piece piece);
	bool getUpgrade();
	void setUpgrade();
	bool gettwoStepChance();
	void settwoStepChance();
	bool getmovedTwoStepsBefore();
	void setmovedTwoStepsBefore();
};

#endif
