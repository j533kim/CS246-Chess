#ifndef _OBSERVER_H_
#define _OBSERVER_H_

// this is from a4q5, some modification is needed

template <typename StateType> class Subject;
class Cell;

template <typename StateType> class Observer {
 public:
  virtual void notify(Subject<StateType> &whoFrom) = 0;
  virtual ~Observer() = default;
};
#endif
