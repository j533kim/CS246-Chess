#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "computer.h"

using namespace std;

string ourpos_to_user(int row, int col) {
	string part_1;
	string part_2;
	if (col == 0) part_1 = "a";
	if (col == 1) part_1 = "b";
	if (col == 2) part_1 = "c";
	if (col == 3) part_1 = "d";
	if (col == 4) part_1 = "e";
	if (col == 5) part_1 = "f";
	if (col == 6) part_1 = "g";
	if (col == 7) part_1 = "h";
	if (row == 0) part_2 = "8";
	if (row == 1) part_2 = "7";
	if (row == 2) part_2 = "6";
	if (row == 3) part_2 = "5";
	if (row == 4) part_2 = "4";
	if (row == 5) part_2 = "3";
	if (row == 6) part_2 = "2";
	if (row == 7) part_2 = "1";
	return part_1 + part_2;
}

void computer_1(Board &b, Color color) {
	std::vector<shared_ptr<Piece>> MyPieces;               // confirm whether store piece or piece ptr
	std::vector<std::vector<Int>> Row_Col;    // stores the row and col index for the my pieces array
	int totalpieces = 0;                     // total no. of pieces in MyPieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (Color::color == Color::White) {
    	w_turn = true;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::White) {
					MyPieces.at(totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col.at(totalpieces).at(0) = i;
					Row_Col.at(totalpieces).at(0) = j;
					++totalpieces;
				}
			}
		}
	} else {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::Black) {
					MyPieces.at(totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col.at(totalpieces).at(0) = i;
					Row_Col.at(totalpieces).at(0) = j;
					++totalpieces;
				}
			}
		}
	}
	int index_array[totalpieces] = 0;              // stores if the Piece at a specific index of MyPieces has been tried. 0 for no and 1 for yes
    for (int k = 0; k < totalpieces; ++k) {
    	int piece_index = rand() % totalpieces;
    	while(index_array[piece_index] == 1) {
    		piece_index = rand() % totalpieces;
    	}
    	for (int l = 0; l < ; ++l) {
    		int row = rand() % 8;
    		int col = rand() % 8;
    		if (b.canmove(MyPieces.at(piece_index).getName(), Row_Col.at(piece_index).at(0), Row_Col.at(piece_index).at(1), row, col)) {
    			b.move(initial, final, w_turn); // confirm the format for initial and final positions
    			//add the notify function 
    			return;
    		} 
    	}
    	index_array[piece_index] = 1;
    }
    // if random cases don't work
    for (int m = 0; m < totalpieces; ++m) {
    	for (int r = 0; r < 8; ++r) {
    		for (int c = 0; c < 8; ++c) {
    			if (b.canmove(MyPieces.at(m).getName(), Row_Col.at(m).at(0), Row_Col.at(m).at(1), r, c)) {
    				b.move(initial, final, w_turn); // confirm the format for initial and final positions
    				//add the notify function 
    				return;
    			} 
    		}
    	}
    }
}

void computer_2(Board &b, Color color) {
	std::vector<shared_ptr<Piece>> MyPieces;
	std::vector<shared_ptr<Piece>> OpPieces;              // stores the opposition pieces
	std::vector<std::vector<Int>> Row_Col_MyPieces;    // stores the row and col index for the my pieces array
	std::vector<std::vector<Int>> Row_Col_OpPieces;    // stores the row and col index for the opposition pieces array
	int my_totalpieces = 0;                     // total no. of pieces in MyPieces array
	int op_totalpieces = 0;                     // total no. of pieces in OpPieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (Color::color == Color::White) {
    	w_turn = true;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::White) {
					MyPieces.at(my_totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col_MyPieces.at(my_totalpieces).at(0) = i;
					Row_Col_MyPieces.at(my_totalpieces).at(0) = j;
					++my_totalpieces;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::Black) {
					OpPieces.at(op_totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col_OpPieces.at(op_totalpieces).at(0) = i;
					Row_Col_OpPieces.at(op_totalpieces).at(0) = j;
					++op_totalpieces;
				}
			}
		}
	} else {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::Black) {
					MyPieces.at(my_totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col_MyPieces.at(my_totalpieces).at(0) = i;
					Row_Col_MyPieces.at(my_totalpieces).at(0) = j;
					++my_totalpieces;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.at(i).at(j).getPiece()->getColor() == Color::White) {
					OpPieces.at(op_totalpieces) = b.at(i).at(j).getPiece(); 
					Row_Col_OpPieces.at(op_totalpieces).at(0) = i;
					Row_Col_OpPieces.at(op_totalpieces).at(0) = j;
					++op_totalpieces;
				}
			}
		}
	}
	int index_capture[op_totalpieces] = 0;
	int index_maxcapture = 0;
	int max  = 0;
	for (int l = 0; l < op_totalpieces; ++l) {
		for (int k = 0; k < op_totalpieces; ++k) {
			if (index_capture[k] == 0) {
				if (OpPieces.at(k)->getValue() > max) {
					max = OpPieces.at(k)->getValue()
					index_maxcapture = k;
				}
			}
		}
		for (int m = 0; m < my_totalpieces; ++m) {
			if (b.canmove(MyPieces.at(m).getName(), Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1), Row_Col_OpPieces.at(k).at(0), Row_Col_OpPieces.at(k).at(1))) {
    			b.move(initial, final, w_turn); // confirm the format for initial and final positions
    			return;
    		} 
		}
		index_capture[k] = 1;
		max = 0;
		index_maxcapture = 0;
	}
return;
}

void computer_3(Board &b, Color color) {
return;
}

void computer_4(Board &b, Color color) {
return;
}
