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
	string name;
public:
	Pawn(Color color, bool twoStepChance);
	void upgrade(Piece piece);
	bool getUpgrade();
	void setUpgrade();
	bool gettwoStepChance();
	void settwoStepChance();
};

#endif
