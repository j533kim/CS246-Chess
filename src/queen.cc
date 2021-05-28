#include "queen.h"

using namespace std;

Queen::Queen(Color color): Piece{color, 9, "queen"}, pawnPromotion{false} {}

bool Queen::getpawnPromotion() const {
	return pawnPromotion;
}

void Queen::setpawnPromotion(bool value) {
	pawnPromotion = value;
}
