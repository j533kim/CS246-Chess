#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include "piece.h"
#include "obersver.h"
#include "subject.h"
#include "color.h"
#include "board.h"

class cell : public Observer<State>, public Subject<State> {
	Piece *piece;
	


}
#endif
