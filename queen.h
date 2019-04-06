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
};

#endif
