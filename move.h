#ifndef _MOVE_
#define _MOVE_
#include "piece.h"
#include <memory>


struct row_col{
	int row;
	int col;
	bool operator==(row_col other) {
		if (row == other.row && col == other.col) {
			return true;
		} else {
			return false;
		}
	}
};


class Move {
	row_col start;
	row_col end;
	std::shared_ptr<Piece> lostPiece;
	std::shared_ptr<Piece> addedPiece; // for pawnPromotion usually // 
	bool officialMove;
public:
	Move() {}
	Move(row_col start, row_col end, std::shared_ptr<Piece> lostPiece, std::shared_ptr<Piece> addedPiece, bool officialMove): start{start}, end{end}, lostPiece{lostPiece}, addedPiece{addedPiece}, officialMove{officialMove} {}
	void setStart(row_col start);
	row_col getStart();
	void setEnd(row_col end);
	row_col getEnd();
	void setLostPiece(std::shared_ptr<Piece> LP);
	std::shared_ptr<Piece> getLostPiece();
	void setAddedPiece(std::shared_ptr<Piece> addedPiece);
	std::shared_ptr<Piece> getepLostPiece();
	void setOfficialMove(bool state);
	bool getOfficialMove();
};

#endif

