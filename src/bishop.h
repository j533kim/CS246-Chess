#ifndef _BISHOP_H_
#define _BISHOP_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "color.h"

class Bishop : public Piece {
public:
	Bishop(Color color);
};

#endif
