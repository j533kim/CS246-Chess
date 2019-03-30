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
	void upgrade(std::shared_ptr<Piece> piece);
};

#endif
