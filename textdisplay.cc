#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() {
	vector<char> vect_odd; // white colored cell first (just space)
	vector<char> vect_even;
	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) {
			vect_even.emplace_back(' ');
			vect_odd.emplace_back('_');
		} else {
			vect_even.emplace_back('_');
			vect_odd.emplace_back(' ');
		}
	}
	for (int i = 0; i < 8; ++i) {
		if (i % 2 == 0) theDisplay.emplace_back(vect_even);
		else theDisplay.emplace_back(vect_odd);
	}
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) out << td.theDisplay.at(i).at(j);
		out << endl;
	}
	return out;
}
