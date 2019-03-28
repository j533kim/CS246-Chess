// CS246 Winter 2019 A5 Chess (By Jiwook, Nipun, and PP)
#include <iostream>
#include <string>
#include <memory>
#include "board.h"
#include "main_helper.h"
#include "observer.h"
#include "subject.h"
#include "computer.h"
#include "color.h"
#include "cell.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "state.h"
//#include "graphicaldisplay.h"

using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Board b;
  float white_score = 0; // if white wins, +1 (if draw, +0.5 each)
  float black_score = 0; // if black wins, +1
  bool white_turn = 1; // it's white's turn if true, and black's otherwise
  bool game_manually_set = false;
  try {
  	while (true) {
  		cin >> cmd;
  		b.init(); // makes a new empty board and deletes previous pieces if necessary
  		if (cmd == "setup") { // enters the setup mode
  			cout << "Now you are in setup mode..." << endl;
  			string setup_cmd, setup_cmd_1, setup_cmd_2;
        cout << b;
  			while (true) {
  				cin >> setup_cmd;
  				if (setup_cmd == "done") { // trying to finish setup mode
  					if (b.setup_valid()) { // checks if setup is valid
  						game_manually_set = true; // tells the game is manually set
  						cout << "setup complete!" << endl;
  						cout << "exiting setup mode" << endl;
  						break; // exiting setup mode
  					} else { // setup is invalid, the user cannot exit setup mode
  						cout << "Hmmm... Your board setup seems inappropriate." << endl;
  						cout << "You are not allowed to leave, make some changes:" << endl;
              cout << b;
  						continue;
  					}
  				} else if (setup_cmd == "+") { // adding a piece in setup
  					cin >> setup_cmd_1 >> setup_cmd_2;
  					try {
  						b.placePiece_setup(setup_cmd_1, setup_cmd_2);
  						cout << b;
  					} catch (InvalidMove In) {
              cout << b;
  						cout << "You cannot place " << setup_cmd_1 << " on ";
  						cout << setup_cmd_2 << ". Try again." << endl;
  						continue;
  					}
  				} else if (setup_cmd == "-") { // removing a piece in setup
  					cin >> setup_cmd_1;
  					b.removePiece_setup(setup_cmd_1); // does nothing if piece is not there
  					cout << b;
  				} else if (setup_cmd == "=") { // color
  					cin >> setup_cmd_1;
  					if ("black" == lowercase(setup_cmd_1)) {
  						cout << "Now black-player starts first!" << endl;
  						white_turn = 0; // now black starts first
  					} else {
  						cout << "Now white-player starts first!" << endl;
  						white_turn = 1;
  					}
  					// nothing happens otherwise
  				}
  			}
  		} else if (cmd == "game") { // game start
  			string game_cmd, game_cmd_1, game_cmd_2;
  			cin >> game_cmd_1 >> game_cmd_2; // cin >> whiteplayer >> blackplayer
  			int player1_level, player2_level;
  			if (!game_manually_set) { // if the game is not set by user (default game)
  				cout << "Default Game Start" << endl;
  				b.game_default_setting();
  			} else {
  				cout << "Setup Game Start" << endl;
  			}
  			cout << game_cmd_1 << "(W) vs " << game_cmd_2 << "(B)" << endl;
        cout << b;
  			// human if level=0; if 1,2,3,4, it's a computer with that level
  			player1_level = determine_level(game_cmd_1); // white player
  			player2_level = determine_level(game_cmd_2); // black player
  			if ((player1_level == 0) && (player2_level == 0)) { // 2 humans
  				while (true) {
  					cin >> game_cmd;
  					if (game_cmd == "resign") {
  						if (white_turn) { // white resigns --> black wins
  							black_score+=1; // black earns a point
                cout << "white_player resigned!" << endl;
  							cout << "black_player wins! Gets 1 point!" << endl;
  						} else { // black resigns --> white wins
  							white_score+=1; // white earns a point
                cout << "black_player resigned!" << endl;
  							cout << "white_player wins! Gets 1 point!" << endl;
  						}
  						break;
  					} else if (game_cmd == "move") {
  						cin >> game_cmd_1 >> game_cmd_2;
  						try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  							b.move(game_cmd_1, game_cmd_2, white_turn);
                cout << b;
  						} catch (InvalidMove In) { // when the move is invalid
  							continue;
  						}
  						if (white_turn == 1) white_turn = 0; // turn changes
  						else white_turn = 1;
  					}
  					if (b.gameEnd()) { // always check if the game is over
  						if (b.winner() == Color::Black) {
  							black_score+=1; // black earns a point
  							cout << "black_player wins! Gets 1 point!" << endl;
  						} else if (b.winner() == Color::White) {
  							white_score+=1; // white earns a point
  							cout << "white_player wins! Gets 1 point!" << endl;
  						} else { // Stalemate or simply draw
  							white_score+=0.5;
  							black_score+=0.5;
  							cout << "it's a draw! Players get 0.5 point each" << endl;
  						}
  						break;
  					}
  				}
  				white_turn = 1; // resetting so white can start in new game
  			} else if (player1_level * player2_level == 0) { // 1 computer and 1 human
  				if (player1_level == 0) { // human is white, human starts first
  					while (true) {
  						if (white_turn) { // human's turn
  							cin >> game_cmd;
  							if (game_cmd == "resign") {
  								black_score+=1; // black earns a point
  								white_turn = 1; // resetting so white can start in new game
  								break;
  							} else if (game_cmd == "move") {
  								cin >> game_cmd_1 >> game_cmd_2;
  								try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  									b.move(game_cmd_1, game_cmd_2, white_turn);
                    cout << b;
  								} catch (InvalidMove In) { // when the move is invalid
                    cout << "Invalid move... Try again." << endl;
  									continue;
  								}
  								white_turn = 0; // turn changes
  							}
  						} else { // computer's turn
  							if (player1_level == 1) {
  								computer_1(b, Color::Black); // computer's move
  							} else if (player1_level == 2) {
  								computer_2(b, Color::Black);
  							} else if (player1_level == 3) {
  								computer_3(b, Color::Black);
  							} else { // computer level 4
  								computer_4(b, Color::Black);
  							}
                cout << b;
  							white_turn = 1; // making it human's turn again
  						}
  						if (b.gameEnd()) { // always check if the game is over
  							if (b.winner() == Color::Black) {
  								black_score+=1; // black earns a point
  								cout << "black_player wins! Gets 1 point!" << endl;
  							} else if (b.winner() == Color::White) {
  								white_score+=1; // white earns a point
  								cout << "white_player wins! Gets 1 point!" << endl;
  							} else { // Stalemate or simply draw
	  							white_score+=0.5;
  								black_score+=0.5;
  								cout << "it's a draw! Players get 0.5 point each" << endl;
  							}
  							break;
  						}
  					}
  					white_turn = 1; // resetting so white can start in new game
  				} else { // computer is white, computer starts first
  					while (true) {
  						if (white_turn) { // computer's turn
  							if (player1_level == 1) {
  								computer_1(b, Color::White); // computer's move
  							} else if (player1_level == 2) {
  								computer_2(b, Color::White);
  							} else if (player1_level == 3) {
  								computer_3(b, Color::White);
  							} else { // computer level 4
  								computer_4(b, Color::White);
  							}
                cout << b;
  							white_turn = 0; // making it human's turn again
  						} else { // human's turn
  							cin >> game_cmd;
  							if (game_cmd == "resign") {
  								++white_score; // white earns a point
  								white_turn = 1; // resetting so white can start in new game
  								break;
  							} else if (game_cmd == "move") {
  								cin >> game_cmd_1 >> game_cmd_2;
  								try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  									b.move(game_cmd_1, game_cmd_2, white_turn);
                    cout << b;
  								} catch (InvalidMove In) { // when the move is invalid
                    cout << "Invalid move... Try again." << endl;
  									continue;
  								}
  								white_turn = 1; // turn changes
  							}
  						}
  						if (b.gameEnd()) { // always check if the game is over
  							if (b.winner() == Color::Black) {
  								++black_score; // black earns a point
  								cout << "black_player wins! Gets 1 point!" << endl;
  							} else if (b.winner() == Color::White) {
  								white_score+=1; // white earns a point
  								cout << "white_player wins! Gets 1 point!" << endl;
  							} else { // Stalemate or simply draw
	  							white_score+=0.5;
  								black_score+=0.5;
  								cout << "it's a draw! Players get 0.5 point each" << endl;
  							}
  							break;
  						}  				
  					}
  					white_turn = 1; // resetting so white can start in new game
  				}
  			} else { // 2 computers
  				while (true) {
  					if (white_turn) { // computer's turn
  						if (player1_level == 1) {
  							computer_1(b, Color::White); // computer's move
  						} else if (player1_level == 2) {
  							computer_2(b, Color::White);
  						} else if (player1_level == 3) {
  							computer_3(b, Color::White);
  						} else { // computer level 4
  							computer_4(b, Color::White);
  						}
              cout << b;
  						white_turn = 0; // making it human's turn again
  					} else { // computer's turn
  						if (player1_level == 1) {
  							computer_1(b, Color::Black); // computer's move
  						} else if (player1_level == 2) {
  							computer_2(b, Color::Black);
  						} else if (player1_level == 3) {
  							computer_3(b, Color::Black);
  						} else { // computer level 4
  							computer_4(b, Color::Black);
  						}
              cout << b;
  						white_turn = 1; // making it human's turn again
  					}
  					if (b.gameEnd()) { // always check if the game is over
  						if (b.winner() == Color::Black) {
  							++black_score; // black earns a point
  							cout << "black_player wins! Gets 1 point!" << endl;
  						} else if (b.winner() == Color::White) {
  							++white_score; // white earns a point
  							cout << "white_player wins! Gets 1 point!" << endl;
  						} else { // Stalemate or simply draw
  							white_score+=0.5;
  							black_score+=0.5;
  							cout << "it's a draw! Players get 0.5 point each" << endl;
  						}
  						break;
  					}
  				}
  				white_turn = 1; // resetting so white can start in new game
  			}
  		}
  	}
  } catch (ios::failure &) { // Any I/O failure quits
    score_print(white_score, black_score); // prints the scoreboard
	}
  return 0; // program ends
}
