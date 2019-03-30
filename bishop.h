#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class Bishop : public Piece {
public:
	Bishop(Color color);
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
