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
	bool gettwoStepChance() const;
	bool getmovedTwoStepsBefore() const;
	bool getUpgrade() const;
	void setUpgrade();
	void setCastle();
	void setCheck();
	void settwoStepChance();
	void setmovedTwoStepsBefore();
	void upgrade(shared_ptr<Piece> piece);
};

#endif
