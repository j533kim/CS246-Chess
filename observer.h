#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "cell.h"
#include "subject.h"
#include "board.h"
#include <memory>
#include "piece.h"
// this is from a4q5, some modification is needed

template <typename StateType> class Subject;
class Cell;
class Board;

template <typename StateType> class Observer {
 public:
  virtual void notify(Subject<StateType> &whoFrom);
  virtual int getRow() const;
  virtual int getCol() const;
  virtual std::shared_ptr<Piece> getPiece() const;
  virtual ~Observer() = default;
};
#endif
