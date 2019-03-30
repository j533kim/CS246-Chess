#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <memory>
#include <string>
#include "color.h"

class Piece {
	Color color;
	int value;
	// value of the piece [pawn=1, knight,bishop=3, rook=5, queen=9, king=10]
	std::string name;
public:
	Piece(Color color, int value, std::string name);
	std::string getName() const;
	int getValue() const;
	bool attacked() const;
	bool attacking() const;
	Color getColor() const;
	virtual void upgrade(shared_ptr<Piece> piece);
	virtual bool getCheck() const;
	virtual bool getCastle() const;
	virtual bool gettwoStepChance() const;
	virtual bool getmovedTwoStepsBefore() const;
	virtual bool getUpgrade() const ;
	virtual void setUpgrade();
	virtual void setCastle();
	virtual void setCheck();
	virtual void settwoStepChance();
	virtual void setmovedTwoStepsBefore();
};

#endif
