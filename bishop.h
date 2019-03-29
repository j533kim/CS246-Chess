#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"

class Bishop : public Piece {
public:
	Bishop(Color color): Piece{color, 3, "bishop"} {}
};

#endif
