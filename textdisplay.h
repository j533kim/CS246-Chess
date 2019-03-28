#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>
#include "color.h"
#include "cell.h"
#include "state.h"

class Cell;

class TextDisplay: public Observer<State> {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay();
  void notify(Subject<State> &whoNotified) override;
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif
