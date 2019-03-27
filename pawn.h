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
	//// let's think about en Passan later...
public:
	Pawn(Color color, int value, bool readyToUpgrade, bool twoStepChance): Piece{color, value}, readyToUpgrade{readyToUpgrade}, twoStepChance{twoStepChance} {}
	void upgrade(Piece piece);
	bool getUpgrade();
	void setUpgrade();
};

#endif
