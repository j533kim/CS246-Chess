#include "move.h"
using namespace std;

void Move::setLostPiece(shared_ptr<Piece> LP) { lostPiece = LP; }

shared_ptr<Piece> Move::getLostPiece() { return lostPiece; }

void Move::setAddedPiece(shared_ptr<Piece> addedPiece) { addedPiece = addedPiece; }

shared_ptr<Piece> Move::getepLostPiece() { return addedPiece; }

void Move::setOfficialMove(bool state) { officialMove = state; }

bool Move::getOfficialMove() { return officialMove; }
