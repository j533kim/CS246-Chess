#include "move.h"
using namespace std;

void Move::setStart(row_col start) { start = start; }

row_col Move::getStart() { return start; }

void Move::setEnd(row_col end) { end = end; }

row_col Move::getEnd() { return end; }

void Move::setLostPiece(shared_ptr<Piece> LP) { lostPiece = LP; }

shared_ptr<Piece> Move::getLostPiece() { return lostPiece; }

void Move::setAddedPiece(shared_ptr<Piece> addedPiece) { addedPiece = addedPiece; }

shared_ptr<Piece> Move::getepLostPiece() { return addedPiece; }

void Move::setOfficialMove(bool state) { officialMove = state; }

bool Move::getOfficialMove() { return officialMove; }
