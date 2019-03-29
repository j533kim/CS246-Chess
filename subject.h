#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "piece.h"
#include "cell.h"
#include "observer.h"

// this whole file is from a4q5, so modification needed


template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<Observer<StateType>*> observers;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers();
  virtual int getRow() const;
  virtual int getCol() const;
  virtual Piece *getPiece() const;
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
