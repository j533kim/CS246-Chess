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
	vector<shared_ptr<Piece>> MyPieces;               // confirm whether store piece or piece ptr
	vector<vector<int>> Row_Col;    // stores the row and col index for the my pieces array
	int totalpieces = 0;                     // total no. of pieces in MyPieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (color == Color::White) {
    	w_turn = 1;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col.emplace_back(vc);
					totalpieces += 1;
				}
			}
		}
	} else {
		w_turn = 0;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col.emplace_back(vc);
					totalpieces += 1;
				}
			}
		}
	}
	vector<int> index_array; // stores if the Piece at a specific index of MyPieces has been tried. 0 for no and 1 for yes
	for (int a = 0; a < totalpieces; ++a) {
		index_array.emplace_back(0);
	}              
    for (int k = 0; k < totalpieces; ++k) {
    	int piece_index = rand() % totalpieces;
    	while(index_array[piece_index] == 1) {
    		piece_index = rand() % totalpieces;
    	}
    	for (int l = 0; l < 1000; ++l) { // decide the no of moves that we want to make 
    		int row = rand() % 8;
    		int col = rand() % 8;
    		if (b.canmove(MyPieces.at(piece_index)->getName(), Row_Col.at(piece_index).at(0), Row_Col.at(piece_index).at(1), row, col)) {
    			string initial = ourpos_to_user(Row_Col.at(piece_index).at(0), Row_Col.at(piece_index).at(1));
    			string final = ourpos_to_user(row, col);
    			try {
    				b.move(initial, final, w_turn);
    				return;
    			} catch (InvalidMove In) {
    				if(w_turn == 1) {
    					computer_1(b, Color::White);
    				} else {
    					computer_1(b, Color::Black);
    				}	
    			} 
    		} 
    	}
    	index_array.at(piece_index) = 1;
    }
    // if random cases don't work
    for (int m = 0; m < totalpieces; ++m) {
    	for (int r = 0; r < 8; ++r) {
    		for (int c = 0; c < 8; ++c) {
    			if (b.canmove(MyPieces.at(m)->getName(), Row_Col.at(m).at(0), Row_Col.at(m).at(1), r, c)) {
    				string initial = ourpos_to_user(Row_Col.at(m).at(0), Row_Col.at(m).at(1));
    				string final = ourpos_to_user(r, c);
    				try {
    					b.move(initial, final, w_turn);
    					return;
    				} catch (InvalidMove In) {
    					if(w_turn == 1) {
    						computer_1(b, Color::White);
    					} else {
    						computer_1(b, Color::Black);
    					}	
    				}
    			} 
    		}
    	}
    }
}

void computer_2(Board &b, Color color) {
	vector<shared_ptr<Piece>> MyPieces;
	vector<shared_ptr<Piece>> OpPieces;              // stores the opposition pieces
	vector<vector<int>> Row_Col_MyPieces;    // stores the row and col index for the my pieces array
	vector<vector<int>> Row_Col_OpPieces;    // stores the row and col index for the opposition pieces array
	int my_totalpieces = 0;                     // total no. of pieces in MyPieces array
	int op_totalpieces = 0;                     // total no. of pieces in OpPieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (color == Color::White) {
    	w_turn = 1;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_MyPieces.emplace_back(vc);
					my_totalpieces += 1;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					OpPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_OpPieces.emplace_back(vc);
					op_totalpieces += 1;
				}
			}
		}
	} else {
		w_turn = 0;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_MyPieces.emplace_back(vc);
					my_totalpieces += 1;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					OpPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_OpPieces.emplace_back(vc);
					op_totalpieces += 1;
				}
			}
		}
	}
	vector<int> index_capture;
	for (int a = 0; a < op_totalpieces; ++a) {
		index_capture.emplace_back(0);
	} 
	int index_maxcapture = 0;
	int max = 0;
	for (int l = 0; l < op_totalpieces; ++l) {
		for (int k = 0; k < op_totalpieces; ++k) {
			if (index_capture.at(k) == 0) {
				if (OpPieces.at(k)->getValue() > max) {
					max = OpPieces.at(k)->getValue();
					index_maxcapture = k;
				}
			}
		}
		for (int m = 0; m < my_totalpieces; ++m) {
			if (b.canmove(MyPieces.at(m)->getName(), Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1), Row_Col_OpPieces.at(index_maxcapture).at(0), Row_Col_OpPieces.at(index_maxcapture).at(1))) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1));
    			string final = ourpos_to_user(Row_Col_OpPieces.at(index_maxcapture).at(0), Row_Col_OpPieces.at(index_maxcapture).at(1));
    			try {
    				b.move(initial, final, w_turn);
    				return;
    			} catch (InvalidMove In) {
    				continue;	
    			} 
    		} 
		}
		index_capture.at(index_maxcapture) = 1;
		max = 0;
		index_maxcapture = 0;
	}
	// subsequent code tries to check the king

	// To get the index of king
	int king_index = 0;
	for (int p = 0; p < op_totalpieces; ++p) {
		if (OpPieces.at(p)->getValue() == 10) {
			king_index = p;
		}
	}
	int king_row = Row_Col_OpPieces.at(king_index).at(0);
	int king_col = Row_Col_OpPieces.at(king_index).at(1);
	for (int r = 0; r < my_totalpieces; ++r) {
		if (MyPieces.at(r)->getName() == "pawn") {
			if (w_turn == 1) {
				if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 1, king_col + 1)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + 1, king_col + 1);
	    			try {
	    				b.move(initial, final, w_turn);
	    				return;
	    			} catch (InvalidMove In) {
	    				continue;	
	    			}
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 1, king_col - 1)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + 1, king_col - 1);
	    			try {
	    				b.move(initial, final, w_turn);
	    				return;
	    			} catch (InvalidMove In) {
	    				continue;	
	    			}
	    		}
    		} else {
    			if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 1, king_col + 1)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - 1, king_col + 1);
	    			try {
		    				b.move(initial, final, w_turn);
		    				return;
		    			} catch (InvalidMove In) {
		    				continue;	
		    			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 1, king_col - 1)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - 1, king_col - 1);
	    			try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		    			continue;	
		   			}
    			}
    		}
		}
		if (MyPieces.at(r)->getName() == "knight") {
			if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 2, king_col + 1)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row + 2, king_col + 1);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
			} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 2, king_col - 1)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row + 2, king_col - 1);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
			} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 2, king_col + 1)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row - 2, king_col + 1);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			}  
    		} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 2, king_col - 1)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row - 2, king_col - 1);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
    		} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 1, king_col - 2)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row + 1, king_col - 2);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
			} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + 1, king_col - 2)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row + 1, king_col - 2);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
    		} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 1, king_col + 2)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row - 1, king_col + 2);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
    		} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - 1, king_col - 2)) {
				string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    			string final = ourpos_to_user(king_row - 1, king_col - 2);
    			try {
	    			b.move(initial, final, w_turn);
	    			return;
	    		} catch (InvalidMove In) {
	   				continue;	
	   			} 
    		}
    	}	
		if (MyPieces.at(r)->getName() == "bishop") {
			for (int a = 7; a >= 0; --a) {
				if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			}  
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				}
			} 	
		}
		if (MyPieces.at(r)->getName() == "rook") {
			for (int a = 7; a >= 0; --a) {
				if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				}
			} 
		}
		if (MyPieces.at(r)->getName() == "queen") {
			for (int a = 7; a >= 0; --a) {
				if (b.canmove("bishop", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove("bishop", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove("bishop", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove("bishop", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				}
				if (b.canmove("rook", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row + a, king_col)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row + a, king_col);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				} else if (b.canmove("rook", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row - a, king_col)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row - a, king_col);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			}  
				} else if (b.canmove("rook", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row, king_col + a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row, king_col + a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			}  
				} else if (b.canmove("rook", Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), king_row, king_col - a)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
    				string final = ourpos_to_user(king_row, king_col - a);
    				try {
		    			b.move(initial, final, w_turn);
		    			return;
		    		} catch (InvalidMove In) {
		   				continue;	
		   			} 
				}
			} 	
		}
		if (MyPieces.at(r)->getName() == "king") {
			continue;
		}
	}
	if (w_turn == 1) {
		computer_1(b, Color::White);
	} else {
		computer_1(b, Color::Black);
	}
}

void computer_3(Board &b, Color color) {
	vector<shared_ptr<Piece>> Pieces;            
	vector<vector<int>> Row_Col;    // stores the row and col index for the pieces vector
	int totalpieces = 0;                     // total no. of pieces in Pieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (color == Color::White) {
    	w_turn = 1;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					if (b.get_theBoard().at(i).at(j).getState().W == Danger::Yes) {
						Pieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
						vc.emplace_back(i);
						vc.emplace_back(j);
						Row_Col.emplace_back(vc);
						totalpieces += 1;
					}
				}
			}
		}
	} else {
		w_turn = 0;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					if (b.get_theBoard().at(i).at(j).getState().B == Danger::Yes) {
						Pieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
						vc.emplace_back(i);
						vc.emplace_back(j);
						Row_Col.emplace_back(vc);
						totalpieces +=1 ;
					}
				}
			}
		}
	}
	vector<int> index_avoidcapture; // stores if the Piece at a specific index of Pieces vector has been tried. 0 for no and 1 for yes
	for (int a = 0; a < totalpieces; ++a) {
		index_avoidcapture.emplace_back(0);
	}
	int index_avoidfirst = 0;
	int max = 0;
	for (int l = 0; l < totalpieces; ++l) {
		for (int k = 0; k < totalpieces; ++k) {
			if (index_avoidcapture.at(k) == 0) {
				if (Pieces.at(k)->getValue() > max) {
					max = Pieces.at(k)->getValue();
					index_avoidfirst = k;
				}
			}
		}
		int r = index_avoidfirst;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (b.canmove(Pieces.at(r)->getName(), Row_Col.at(r).at(0), Row_Col.at(r).at(1), i, j) && 
					(Row_Col.at(r).at(0) != i) && (Row_Col.at(r).at(1) != j)) {
					string initial = ourpos_to_user(Row_Col.at(r).at(0), Row_Col.at(r).at(1));
   					string final = ourpos_to_user(i, j);
   				    try {
   						b.move(initial, final, w_turn);
   						return;
   				    } catch (InvalidMove In) {
   						continue;	
    				} 
				}
			}
		}
		index_avoidcapture.at(index_avoidfirst) = 1;
		max = 0;
		index_avoidfirst = 0;
	}  
	if (w_turn == 1) {
		computer_2(b, Color::White);
	} else {
		computer_2(b, Color::Black);
	}	 	
} 

void computer_4(Board &b, Color color) {
	vector<shared_ptr<Piece>> MyPieces;
	vector<shared_ptr<Piece>> OpPieces;              // stores the opposition pieces
	vector<vector<int>> Row_Col_MyPieces;    // stores the row and col index for the my pieces array
	vector<vector<int>> Row_Col_OpPieces;    // stores the row and col index for the opposition pieces array
	int my_totalpieces = 0;                     // total no. of pieces in MyPieces array
	int op_totalpieces = 0;                     // total no. of pieces in OpPieces array
	bool w_turn = 0;                         // equals 1 when it's whites's turn
	if (color == Color::White) {
    	w_turn = 1;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_MyPieces.emplace_back(vc);
					my_totalpieces += 1;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					OpPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_OpPieces.emplace_back(vc);
					op_totalpieces += 1;
				}
			}
		}
	} else {
		w_turn = 0;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::Black) {
					MyPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_MyPieces.emplace_back(vc);
					my_totalpieces += 1;
				}
			}
		}
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				vector<int> vc; 
				if (b.get_theBoard().at(i).at(j).getPiece()->getColor() == Color::White) {
					OpPieces.emplace_back(b.get_theBoard().at(i).at(j).getPiece()); 
					vc.emplace_back(i);
					vc.emplace_back(j);
					Row_Col_OpPieces.emplace_back(vc);
					op_totalpieces += 1;
				}
			}
		}
	}
	vector<int> index_capture;
	for (int a = 0; a < op_totalpieces; ++a) {
		index_capture.emplace_back(0);
	} 
	int index_maxcapture = 0;
	int max = 0;
	for (int l = 0; l < op_totalpieces; ++l) {
		for (int k = 0; k < op_totalpieces; ++k) {
			if (index_capture.at(k) == 0) {
				if (OpPieces.at(k)->getValue() > max) {
					max = OpPieces.at(k)->getValue();
					index_maxcapture = k;
				}
			}
		}
		for (int m = 0; m < my_totalpieces; ++m) {
			int final_row = Row_Col_OpPieces.at(index_maxcapture).at(0);
			int final_col = Row_Col_OpPieces.at(index_maxcapture).at(1);
			if (w_turn == 1) {
				if (b.canmove(MyPieces.at(m)->getName(), Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1), final_row, final_col) &&
					(b.get_theBoard().at(final_row).at(final_col).getState().W == Danger::No)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1));
	    			string final = ourpos_to_user(final_row, final_col);
	    			try {
   						b.move(initial, final, w_turn);
   						return;
   				    } catch (InvalidMove In) {
   						continue;	
    				} 
			} else {
				if (b.canmove(MyPieces.at(m)->getName(), Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1), final_row, final_col) &&
					(b.get_theBoard().at(final_row).at(final_col).getState().B == Danger::No)) {
					string initial = ourpos_to_user(Row_Col_MyPieces.at(m).at(0), Row_Col_MyPieces.at(m).at(1));
	    			string final = ourpos_to_user(final_row, final_col);
	    			try {
   						b.move(initial, final, w_turn);
   						return;
   				    } catch (InvalidMove In) {
   						continue;	
    				} 
	    		}
			}	
		}
		index_capture.at(index_maxcapture) = 1;
		max = 0;
		index_maxcapture = 0;
	}
	/* vector<int> index_avoidcapture; // stores if the Piece at a specific index of Pieces vector has been tried. 0 for no and 1 for yes
	for (int a = 0; a < my_totalpieces; ++a) {
		index_avoidcapture.emplace_back(0);
	}
	int index_avoidfirst = 0;
	int avoid_max = 0;
	for (int l = 0; l < my_totalpieces; ++l) {
		for (int k = 0; k < my_totalpieces; ++k) {
			if (index_avoidcapture.at(k) == 0) {
				if (MyPieces.at(k)->getValue() > avoid_max) {
					avoid_max = MyPieces.at(k)->getValue();
					index_avoidfirst = k;
				}
			}
		}
		int r = index_avoidfirst;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (w_turn == 1) {
					if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), i, j) && 
						(Row_Col_MyPieces.at(r).at(0) != i) && (Row_Col_MyPieces.at(r).at(1) != j) &&
						(b.get_theBoard().at(i).at(j).getState().W == Danger::No)) {
						string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
	   					string final = ourpos_to_user(i, j);
	   					try {
	   						b.move(initial, final, w_turn);
	   						return;
	   				    } catch (InvalidMove In) {
	   						continue;	
	    				} 
					}
				} else {
					if (b.canmove(MyPieces.at(r)->getName(), Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1), i, j) && 
						(Row_Col_MyPieces.at(r).at(0) != i) && (Row_Col_MyPieces.at(r).at(1) != j) &&
						(b.get_theBoard().at(i).at(j).getState().B == Danger::No)) {
						string initial = ourpos_to_user(Row_Col_MyPieces.at(r).at(0), Row_Col_MyPieces.at(r).at(1));
	   					string final = ourpos_to_user(i, j);
	   					try {
	   						b.move(initial, final, w_turn);
	   						return;
	   				    } catch (InvalidMove In) {
	   						continue;	
	    				} 
					}
				}	
			}
		} 
		index_avoidcapture.at(index_avoidfirst) = 1;
		avoid_max = 0;
		index_avoidfirst = 0;
	} */
	if (w_turn == 1) {
		computer_3(b, Color::White);
	} else {
		computer_3(b, Color::Black);
	} 	
} 
