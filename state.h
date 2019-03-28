#ifndef _STATE_H_
#define _STATE_H_

enum class StateType_B {UA, Safe};
enum class StateType_W {UA, Safe};
//enum class Colour { NoColour, Black, White };
// enum class Direction { NW, N, NE, W, E, SW, S, SE };

struct State {
  StateType_W type_W;  // See above
  StateType_B type_B;
};

#endif
