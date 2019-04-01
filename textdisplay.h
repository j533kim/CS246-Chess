#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "color.h"
#include "cell.h"
#include "state.h"
#include "observer.h"
#include "subject.h"
#include "piece.h"

class Cell;
class Board;
template <typename StateType> class Subject;

class TextDisplay: public Observer<State> {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay();
  void notify(Subject<State> &whoNotified) override;
  int getRow() const override {}
  int getCol() const override {}
  std::shared_ptr<Piece> getPiece() const override {}
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
