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
	bool getUpgrade() const;
	void setUpgrade();
	bool gettwoStepChance() const;
	void settwoStepChance();
	bool getmovedTwoStepsBefore() const;
	void setmovedTwoStepsBefore();
};

#endif
