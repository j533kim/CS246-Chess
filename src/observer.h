#ifndef _OBSERVER_H_
#define _OBSERVER_H_


// this is from a4q5, some modification is needed

template <typename StateType> class Subject;
class Cell;

template <typename StateType> class Observer {
 public:
  virtual void notify(Subject<StateType> &whoFrom) = 0;
  virtual int getRow() const = 0;
  virtual int getCol() const = 0;
  virtual std::shared_ptr<Piece> getPiece() const = 0;
  virtual ~Observer() = default;
};
#endif
