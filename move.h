#ifndef _MOVE_
#define _MOVE_
#include "piece.h"
#include <memory>

class Move {
	std::shared_ptr<Piece> lostPiece;
	std::shared_ptr<Piece> addedPiece; // for pawnPromotion usually // 
	bool officialMove;
public:
	int row_0;
	int col_0;
	int row_f;
	int col_f;
	Move() {}
	Move(int row_0, int col_0, int row_f, int col_f, std::shared_ptr<Piece> lostPiece, std::shared_ptr<Piece> addedPiece, bool officialMove): row_0{row_0}, col_0{col_0}, row_f{row_f}, col_f{col_f}, lostPiece{lostPiece}, addedPiece{addedPiece}, officialMove{officialMove} {}
	//void setStart(int row_0, int col_0);
	//row_col getStart();
	//void setEnd(int row_f, int col_f);;
	//row_col getEnd();
	void setLostPiece(std::shared_ptr<Piece> LP);
	std::shared_ptr<Piece> getLostPiece();
	void setAddedPiece(std::shared_ptr<Piece> addedPiece);
	std::shared_ptr<Piece> getepLostPiece();
	void setOfficialMove(bool state);
	bool getOfficialMove();
};

#endif

