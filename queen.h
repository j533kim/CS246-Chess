#ifndef _QUEEN_H_
#define _QUEEN_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class Queen : public Piece {
public:
	Queen(Color color);
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
