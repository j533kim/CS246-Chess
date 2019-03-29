#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Piece {
	Color color;
	int value;
	// value of the piece [pawn=1, knight,bishop=3, rook=5, queen=9, king=10]
	std::string name;
public:
	Piece(Color color, int value, std::string name);
	std::string getName() const;
	bool attacked();
	bool attacking();
	Color getColor() const;
	virtual bool getCheck() const;
	//virtual void move() = 0;
	virtual void settwoStepChance(); // pawn's function
	virtual bool gettwoStepChance() const; // pawn's function

};

#endif
