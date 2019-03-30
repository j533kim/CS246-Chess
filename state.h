#ifndef _STATE_H_
#define _STATE_H_

enum class Danger {Yes, No};

struct State {
  Danger W;  // See above
  Danger B;
};

#endif
