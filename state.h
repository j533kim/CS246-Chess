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


/*std::ostream &operator<<(std::ostream &stream, const State &other) {
  	if (other.W == Danger::Yes) {
  		stream << "W : Yes";
  	} else {
  		stream << "W : No"; 
  	}
  	stream << "   ";
  	if (other.B == Danger::Yes) {
  		stream << "B : Yes";
  	} else {
  		stream << "B : No";
  	}
  	stream << std::endl;
  	return stream;
}
*/

#endif
