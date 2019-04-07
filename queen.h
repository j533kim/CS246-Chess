#ifndef _QUEEN_H_
#define _QUEEN_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class Queen : public Piece {
	bool pawnPromotion;
public:
	Queen(Color color);
	//bool getCheck() const;
	//bool getCastle() const;
	//bool gettwoStepChance() const;
	//bool getmovedTwoStepsBefore() const;
	//bool getUpgrade() const;
	//void setUpgrade();
	//void setCastle();
	//void setCheck();
	bool getpawnPromotion() const;
	bool setpawnPromotion(bool value);
	//void settwoStepChance();
	//void setmovedTwoStepsBefore();
	//void upgrade(std::shared_ptr<Piece> piece);
};

#endif
