#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <iostream>
#include <memory>
#include "piece.h"
#include "observer.h"

// this whole file is from a4q5, so modification needed

class Piece;

template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<std::shared_ptr<Observer<StateType>>> observers;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers();
  virtual int getRow() const = 0;
  virtual int getCol() const = 0;
  virtual std::shared_ptr<Piece> getPiece() const = 0;
 // virtual InfoType getInfo() const = 0;
  StateType getState() const;
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
