#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Bishop : public Piece {
	string name;
public:
	Bishop(Color color): Piece{color, 3}, name{"bishop"} {}
}

#endif
