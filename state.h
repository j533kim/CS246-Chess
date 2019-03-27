#ifndef _STATE_H_
#define _STATE_H_

enum class StateType {W_UA, W_Safe B_UA, B_Safe};
//enum class Colour { NoColour, Black, White };
// enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
  StateType type;  // See above
};

#endif