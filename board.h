#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "color.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class Board {
  std::vector<std::vector<Cell>> theBoard;
  TextDisplay *td = nullptr;
  Observer<Info, State> *ob = nullptr;
  bool checkmate = false;
  boo stalemate = false;
public:
  ~Board(); // destructor
  void setObserver(Observer<Info, State> *ob); // sets the observers for each
  void init(); // sets up 8x8 board and responsible for observer pattern
               // clears the old board, if necessary
  void move(std::string pos_initial, std::string pos_final); // move a piece
  void remove(std::string pos); // removes a piece, if nothing, nothing happens
  Color winner(); // white wins -> White, black wins -> Black, draw -> NoColor
  bool gameEnd(); // true if gameover or false otherwise 
  placePiece(std::string piece, std::string pos);
  // placePiece() calls move and remove functions
};

#endif
