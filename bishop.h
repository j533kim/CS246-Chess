#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Bishop : public Piece {

public:
	Bishop(Color color, int value): Piece{color,value} {}
}

#endif
