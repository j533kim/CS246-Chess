#ifndef _QUEEN_H_
#define _QUEEN_H_

#include <vector>
#include <string>
#include "piece.h"
#include "color.h"
#include "board.h"

class Queen : public Piece {
public:
	Queen(Color color, int value): Piece{color, 9} {}
};


#endif
