#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "cell.h"
#include "subject.h"
// this is from a4q5, some modification is needed

template <typename State> class Subject;
class Cell;

template <typename State> class Observer {
 public:
  virtual void notify(Subject<State> &whoFrom) = 0;
  virtual ~Observer() = default;
};
#endif
