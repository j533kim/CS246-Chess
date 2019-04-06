#ifndef _STATE_H_
#define _STATE_H_
#include <iostream>
#include <string>

enum class Danger {Yes, No};

struct State {
  Danger W; // White's perspective
  Danger B; // Black's perspective
  //friend std::ostream &operator<<(std::ostream& stream, State &other);
};

#endif
