#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "cell.h"
#include "board.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include "window.h"
#include <memory>
#include "piece.h"
#include "color.h"
#include <string>


class Cell;
class Board;
template <typename StateType> class Subject;

class GraphicsDisplay : public Observer<State> {
	Xwindow window;
	int gridSize;
public:
	GraphicsDisplay(); // constructor
	void notify(Subject<State> &whoNotified) override; // notify from cells
	~GraphicsDisplay(); // destructor
	int getRow() const override;
  	int getCol() const override;
  	std::shared_ptr<Piece> getPiece() const override;
};
#endif
