#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>
#include "cell.h"

class Cell;

class TextDisplay: public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  TextDisplay(int n);
  void notify(Subject<Info, State> &whoNotified) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
