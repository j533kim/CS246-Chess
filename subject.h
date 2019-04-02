#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <iostream>
#include <memory>
#include "piece.h"
#include "observer.h"
#include "board.h"

class Piece;
class Board;

template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<Observer<StateType> *>observers;
  StateType state;
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers();
  virtual int getRow() const = 0;
  virtual int getCol() const = 0;
  virtual void settheBoard(Board *theBoard) = 0;
  virtual Board *gettheBoard() = 0;
  virtual std::shared_ptr<Piece> getPiece() const = 0;
  StateType getState() const;
  std::vector<Observer<StateType> *> getObservers() { return observers; }
  void setState(StateType newS);
};

template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
  observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }
#endif
