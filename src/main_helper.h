#ifndef _MAIN_HELPER_H_
#define _MAIN_HELPER_H_

#include <iostream>
#include <string>
#include <vector>

std::string lowercase(std::string str); // converts the string into all lowercases

// detemines whether human/computer, if computer, its level
// 0=human, 1=computer1, ..., 4=computer4
int determine_level(std::string playerName);

// prints out the scoreboard when the program has ended
void score_print(float white_score, float black_score);

#endif
