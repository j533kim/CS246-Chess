#ifndef _STATE_H_
#define _STATE_H_

enum class Danger {Yes, No};

struct State {
  Danger W; // White's perspective
  Danger B; // Black's perspective
};

#endif
