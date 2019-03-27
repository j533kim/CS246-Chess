#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Knight : public Piece {
public:
	Knight(Color color, int value): Piece{color, 3} {}
};


#endif
