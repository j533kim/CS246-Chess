#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(): // constructor
window{470, 470}, gridSize{50} {
	
	for (int i = 8; i > 0; --i) {
		window.drawBigString(30, (8 - i) * 50 + 45, std::to_string(i), 1);
	}
	for (char c = 'a'; c < 'i'; ++c) {
		std::string temp = "a";
		temp[0] = c;
		window.drawBigString(50 + 50 * (c - 'a') + 20, 440, temp, 1);	
	}
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 == 0) {
				window.fillRectangle((50 * i) + 50, 50 * j + 10, 50, 50, 0);
			} else {
				window.fillRectangle((50 * i) + 50, 50 * j + 10, 50, 50, 1);
			}
		}
	}
}

int GraphicsDisplay::getRow() const { return 0; }

int GraphicsDisplay::getCol() const { return 0; }

std::shared_ptr<Piece> GraphicsDisplay::getPiece() const { return nullptr; }

void GraphicsDisplay::notify(Subject<State> &whoNotified) {
	int row = whoNotified.getRow();
	int col = whoNotified.getCol();
	std::string name = whoNotified.getPiece()->getName();
	Color color = whoNotified.getPiece()->getColor();
	if (name == "nopiece" || color == Color::NoColor) {
		if ((row + col) % 2 == 0) window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 0);
		else window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 1);
	} else if (color == Color::White) {
		if ((row + col) % 2 == 0) window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 0);
		else window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 1);
		if (name == "king") {
			window.fillRectangle(col * 50 + 40 + 30, row * 50 + 10 + 10, 10, 30, 6);
			window.fillRectangle(col * 50 + 30 + 30, row * 50 + 20 + 10, 30, 10, 6);
		} else if (name == "queen") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 6);

			window.fillCircle(col * 50 + 10 + 50, row * 50 + 25 + 10, 5, 7);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 5, 7);
			window.fillCircle(col * 50 + 10 + 50, row * 50 + 15 + 10, 5, 7);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 10 + 10, 5, 7);

			window.fillCircle(col * 50 + 18 + 50, row * 50 + 18 + 10, 5, 7);
			window.fillCircle(col * 50 + 34 + 50, row * 50 + 34 + 10, 5, 7);
			window.fillCircle(col * 50 + 34 + 50, row * 50 + 18 + 10, 5, 7);
			window.fillCircle(col * 50 + 18 + 50, row * 50 + 34 + 10, 5, 7);
		} else if (name == "knight") {
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 10 + 10, 10, 20, 6);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 30 + 10, 20, 6);
		} else if (name == "bishop") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 6);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 20, 7);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 10, 6);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 24 + 10, 5, 2, 1);
		} else if (name == "rook") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 6);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 10 + 10, 10, 5, 7);
			window.fillRectangle(col * 50 + 10 + 50, row * 50 + 20 + 10, 5, 10, 7);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 35 + 10, 10, 5, 7);
			window.fillRectangle(col * 50 + 35 + 50, row * 50 + 20 + 10, 5, 10, 7);
		} else if (name == "pawn") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 6);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 15, 7);
		}
	} else if (color == Color::Black) {
		if ((row + col) % 2 == 0) window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 0);
		else window.fillRectangle(50 * col + 50, 50 * row + 10, 50, 50, 1);
		if (name == "king") {
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 10 + 10, 10, 30, 9);
			window.fillRectangle(col * 50 + 10 + 50, row * 50 + 20 + 10, 30, 10, 9);
		} else if (name == "queen") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 9);

			window.fillCircle(col * 50 + 10 + 50, row * 50 + 25 + 10, 5, 10);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 5, 10);
			window.fillCircle(col * 50 + 10 + 50, row * 50 + 15 + 10, 5, 10);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 10 + 10, 5, 10);

			window.fillCircle(col * 50 + 18 + 50, row * 50 + 18 + 10, 5, 10);
			window.fillCircle(col * 50 + 34 + 50, row * 50 + 34 + 10, 5, 10);
			window.fillCircle(col * 50 + 34 + 50, row * 50 + 18 + 10, 5, 10);
			window.fillCircle(col * 50 + 18 + 50, row * 50 + 34 + 10, 5, 10);
		} else if (name == "knight") {
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 20 + 10, 10, 20, 9);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 20 + 10, 20, 9);
		} else if (name == "bishop") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 9);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 20, 10);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 10, 9);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 24 + 10, 5, 2, 1);
		} else if (name == "rook") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 9);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 10 + 10, 10, 5, 10);
			window.fillRectangle(col * 50 + 10 + 50, row * 50 + 20 + 10, 5, 10, 10);
			window.fillRectangle(col * 50 + 20 + 50, row * 50 + 35 + 10, 10, 5, 10);
			window.fillRectangle(col * 50 + 35 + 50, row * 50 + 20 + 10, 5, 10, 10);
		} else if (name == "pawn") {
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 30, 9);
			window.fillCircle(col * 50 + 25 + 50, row * 50 + 25 + 10, 15, 10);
		}
	}	
}

GraphicsDisplay::~GraphicsDisplay() {} // destructor
