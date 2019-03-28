#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Knight : public Piece {
	string name;
public:
	Knight(Color color);
};

#endif
