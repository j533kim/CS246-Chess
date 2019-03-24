#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "color.h"
#include "board.h"

using namespace std;

Board::~Board() {
	delete td;
	delete ob;
}

void Board::setObserver(Observer<Info, State> *ob) {

}

void Board::init() {

}

void Board::move(string pos_initial, string pos_final) {

}

void Board::remove(string pos) {

}

Color Board::winner() {

}

bool Board::gameEnd() {

}

bool Board::setup_valid() {

}

void Board::game_default_setting() {

}

void Board::placePiece(string piece, string pos) {

}

ostream &operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	return out;
}
