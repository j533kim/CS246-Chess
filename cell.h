#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "obersver.h"
#include "subject.h"
#include "color.h"
#include "board.h"

class Cell : public Subject<State> public Observer<State> {
	Piece *piece;
	int row;
	int col;
public:
	Cell(Piece piece, int row, int col); // constructor
	void notify(Subject<Info, State> &whoFrom) override;
	void placePiece();
	void placePiece_setup(string piece); // places the piece on the cell
	void removePiece(); // simply removes the piece on the cell
						// and replaces with noPiece
	Piece getPiece();
	int getRow() const;
	int getCol() const;
	~Cell();
};

#endif
