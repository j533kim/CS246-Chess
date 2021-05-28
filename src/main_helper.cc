#include <iostream>
#include <string>
#include <vector>
#include "main_helper.h"

using namespace std;

// this module is perfect, Jiwook has already fully tested

string lowercase(string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (('A' <= str[i]) && (str[i] <= 'Z')) str[i] = str[i] + 'a' -'A';
	}
	return str;
}

int determine_level(string playerName) {
	if (playerName.length() == 9) {
		string name_low = lowercase(playerName.substr(0, 8));
		string back_num = playerName.substr(8, 9);
		if (name_low == "computer") {
			if (back_num == "1") return 1;
			else if (back_num == "2") return 2;
			else if (back_num == "3") return 3;
			else if (back_num == "4") return 4;
		}
	}
	return 0; // not a computer (human's name)
}

// prints out the scoreboard when the program has ended
void score_print(float white_score, float black_score) {
	cout << "Final Score:" << endl;
	cout << "White: " << white_score << endl;
	cout << "Black: " << black_score << endl;
}
