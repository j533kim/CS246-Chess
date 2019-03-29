#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "observer.h"
#include "subject.h"
#include "color.h"
#include "board.h"
#include "state.h"

class Cell : public Subject<State>, public Observer<State> {
	int row;
	int col;
	Piece *piece;
public:
	Cell(Piece piece, int row, int col); // constructor
	void notify(Subject<State> &whoFrom) override;
	void placePiece();
	void placePiece_setup(std::string piece); // places the piece on the cell
	void removePiece(); // simply removes the piece on the cell
						// and replaces with noPiece
	Piece *getPiece() const override;
	void setPiece(Piece *piece);
	int getRow() const override;
	int getCol() const override;
	~Cell();
};

#endif
