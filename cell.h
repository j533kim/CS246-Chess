#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include <memory>
#include "piece.h"
#include "observer.h"
#include "subject.h"
#include "color.h"
#include "state.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "nopiece.h"
#include "board.h"

class InvalidMove{};
class Piece;
class Board;

class Cell : public Subject<State>, public Observer<State> {
	int row;
	int col;
	Board *theBoard;
	std::shared_ptr<Piece> piece;
public:
	Cell(std::shared_ptr<Piece> piece, int row, int col); // constructor
	void notify(Subject<State> &whoFrom) override;
	void placePiece(std::shared_ptr<Piece> piece);
	void placePiece_setup(std::string piece); // places the piece on the cell
	void removePiece(); // simply removes the piece on the cell
						// and replaces with noPiece
	std::shared_ptr<Piece> getPiece() const override;
	int getRow() const override;
	int getCol() const override;
	void settheBoard(Board *theBoard) override;
	Board *gettheBoard() override;

	//~Cell();
};

#endif
