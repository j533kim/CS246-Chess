#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "cell.h"
#include "textdisplay.h"
//#include "graphicsdisplay.h"
#include "color.h"
#include "main_helper.h"
#include "piece.h"
#include <sstream>

class TextDisplay;
template <typename StateType> class Observer;
class InvalidMove {};

class Board {
  std::vector<std::vector<Cell>> theBoard;
  // I'm not so sure about using these smartpointers (verification needed)
  TextDisplay *td = nullptr;
  Observer<State> *ob = nullptr;
  bool checkmate = false;
  bool stalemate = false;
public:
  ~Board(); // destructor
  void setObserver(Observer<State> *ob); // sets the observers for each
  void init(); // sets up 8x8 board and responsible for observer pattern
               // clears the old board, if necessary
  void move(std::string pos_initial, std::string pos_final, bool white_turn); // move a piece
  void removePiece_setup(std::string pos); // removes a piece, if nothing, nothing happens
  void removePiece(int row, int col);
  Color winner(); // white wins -> White, black wins -> Black, draw -> NoColor
  bool gameEnd(); // true if gameover or false otherwise 
  bool setup_valid(); // determines if the current setup mode is valid
  void game_default_setting(); // places the pieces in right pos in default
  void placePiece_setup(std::string piece, std::string pos);
  void placePiece(Piece &piece, int row, int col);
  void swapPiece(int row_0, int col_0, int row_f, int col_f);
  bool canmove(std::string name, int row_0, int col_0, int row_f, int col_f);
  // placePiece() calls move and remove functions
  // placePiece()'s positions are in the users' perspective (be aware of change)
  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

std::ostream &operator<<(std::ostream &out, const Board &b);

#endif
