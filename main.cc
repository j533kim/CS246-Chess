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
  bool setuped = false;
  int round_num = 0;
  try {
  	while (true) {
      if (!setuped) b.init(); // makes a new empty board and deletes previous pieces if necessary
  		cin >> cmd;
      if (cin.eof() || cin.fail()) throw std::iostream::failure("");
      if (!(cmd == "setup" || cmd == "game")) continue;
  		if (cmd == "setup") { // enters the setup mode
  			cout << "Now you are in setup mode..." << endl;
  			string setup_cmd, setup_cmd_1, setup_cmd_2;
        cout << endl;
        cout << b << endl;
  			while (true) {
  				cin >> setup_cmd;
          
  				if (setup_cmd == "done") { // trying to finish setup mode
  					if (b.setup_valid()) { // checks if setup is valid
  						game_manually_set = true; // tells the game is manually set
  						cout << "setup complete!" << endl;
  						cout << "exiting setup mode" << endl;
              setuped = true;
  						break; // exiting setup mode
  					} else { // setup is invalid, the user cannot exit setup mode
  						cout << "Your board setup seems inappropriate." << endl;
  						cout << "You are not allowed to leave, make some changes:" << endl;
              cout << endl;
              cout << b << endl;
  						continue;
  					}
  				} else if (setup_cmd == "+") { // adding a piece in setup
  					cin >> setup_cmd_1 >> setup_cmd_2;
            
  					try {
  						b.placePiece_setup(setup_cmd_1, setup_cmd_2);
  						cout << endl;
              cout << b << endl;
  					} catch (InvalidMove In) {
  						cout << "You cannot place " << setup_cmd_1 << " on ";
  						cout << setup_cmd_2 << ". Try again." << endl << endl;
  						continue;
  					}
  				} else if (setup_cmd == "-") { // removing a piece in setup
  					cin >> setup_cmd_1;
            
  					b.removePiece_setup(setup_cmd_1); // does nothing if piece is not there
  					cout << endl;
            cout << b << endl;
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
        setuped = false;
  			string game_cmd, game_cmd_1, game_cmd_2;
  			cin >> game_cmd_1 >> game_cmd_2; // cin >> whiteplayer >> blackplayer
        
  			int player1_level, player2_level;
        cout << endl;
  			if (!game_manually_set) { // if the game is not set by user (default game)
  				cout << "Default Game Start" << endl;
  				b.game_default_setting();
  			} else {
  				cout << "Setup Game Start" << endl;
  			}
        game_manually_set = false;
        ++round_num;
        cout << "  ROUND " << round_num << endl;
  			cout << game_cmd_1 << "(W) vs " << game_cmd_2 << "(B)" << endl << endl;
        cout << b << endl;
  			// human if level=0; if 1,2,3,4, it's a computer with that level
  			player1_level = determine_level(game_cmd_1); // white player
  			player2_level = determine_level(game_cmd_2); // black player
  			if ((player1_level == 0) && (player2_level == 0)) { // 2 humans
          b.setHumans(Color::White, true);
          b.setHumans(Color::Black, true);
  				while (true) {
  					cin >> game_cmd;
            
  					if (game_cmd == "resign") {
  						if (white_turn) { // white resigns --> black wins
  							black_score+=1; // black earns a point
                cout << endl << "white_player resigned!" << endl;
  							cout << endl << "black_player wins! Gets 1 point!" << endl;
  						} else { // black resigns --> white wins
  							white_score+=1; // white earns a point
                cout << endl << "black_player resigned!" << endl;
  							cout << endl << "white_player wins! Gets 1 point!" << endl;
  						}
  						break;
  					} else if (game_cmd == "move") {
  						cin >> game_cmd_1 >> game_cmd_2;
              
  						try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  							b.move(game_cmd_1, game_cmd_2, white_turn);
                cout << endl;
                cout << b << endl;
               
                cout << endl;
  						} catch (InvalidMove In) { // when the move is invalid
                cout << "Try again." << endl << endl;
  							continue;
  						}
              //b.setPastCastle(false);
             // b.setPastEmPassant(false);
  						if (white_turn == 1) white_turn = 0; // turn changes
  						else white_turn = 1;
  					} else if (game_cmd == "undo") {
              try {
                b.undo();
                cout << b;
              } catch (InvalidMove in) {
                cout << "you have reached the beginning of the game" << endl;
              }
              if (white_turn == 1) white_turn = 0; // turn changes
              else white_turn = 1;
            } else if (game_cmd == "history") {
              cout << endl;
              b.printHistory(white_turn);
              cout << endl;
            }
  					if (b.gameEnd()) { // always check if the game is over
  						if (b.winner() == Color::Black) {
  							black_score+=1; // black earns a point
  							cout << endl << "black_player wins! Gets 1 point!" << endl;
  						} else if (b.winner() == Color::White) {
  							white_score+=1; // white earns a point
  							cout << endl << "white_player wins! Gets 1 point!" << endl;
  						} else { // Stalemate or simply draw
  							white_score+=0.5;
  							black_score+=0.5;
  							cout << "it's a draw! Players get 0.5 point each." << endl;
  						}
  						break;
  					}
  				}
  				white_turn = 1; // resetting so white can start in new game
  			} else if (player1_level * player2_level == 0) { // 1 computer and 1 human
  				if (player1_level == 0) { // human is white, human starts first
            b.setHumans(Color::White, true);
            b.setHumans(Color::Black, false);
  					while (true) {
  						if (white_turn) { // human's turn
  							cin >> game_cmd;
                
  							if (game_cmd == "resign") {
  								++black_score; // black earns a point
                  cout << "You resigned!" << endl;
                  cout << "computer" << player2_level << "(B) wins! Gets 1 point!" << endl;
  								white_turn = 1; // resetting so white can start in new game
  								break;
  							} else if (game_cmd == "move") {
  								cin >> game_cmd_1 >> game_cmd_2;
                  
  								try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  									b.move(game_cmd_1, game_cmd_2, white_turn);
                    cout << endl;
                    cout << b << endl;
  								} catch (InvalidMove In) { // when the move is invalid
                    cout << "Try again." << endl << endl;
  									continue;
  								}
  								white_turn = 0; // turn changes
  							} else if (game_cmd == "undo") {
                    try {
                      b.undo();
                      cout << b;
                    } catch (InvalidMove in) {
                      cout << "you have reached the beginning of the game" << endl;
                    }
                    if (white_turn == 1) white_turn = 0; // turn changes
                    else white_turn = 1;
                } else if (game_cmd == "history") {
                    cout << endl;
                    b.printHistory(white_turn);
                    cout << endl;
                }
  						} else { // computer's turn
  							if (player2_level == 1) {
  								computer_1(b, Color::Black); // computer's move
  							} else if (player2_level == 2) {
  								computer_2(b, Color::Black);
  							} else if (player2_level == 3) {
  								computer_3(b, Color::Black);
  							} else { // computer level 4
  								computer_4(b, Color::Black);
  							}
                cout << endl;
                cout << b << endl;
  							white_turn = 1; // making it human's turn again
  						}
  						if (b.gameEnd()) { // always check if the game is over
  							if (b.winner() == Color::Black) {
  								black_score+=1; // black earns a point
  								cout << endl << "black_player wins! Gets 1 point!" << endl;
  							} else if (b.winner() == Color::White) {
  								white_score+=1; // white earns a point
  								cout << endl << "white_player wins! Gets 1 point!" << endl;
  							} else { // Stalemate or simply draw
	  							white_score+=0.5;
  								black_score+=0.5;
  								cout << "it's a draw! Players get 0.5 point each." << endl;
  							}
                white_turn = 1; // resetting so white can start in new game
  							break;
  						}
  					}
  				} else { // computer is white, computer starts first
            b.setHumans(Color::White, false);
            b.setHumans(Color::Black, true);
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
                cout << endl;
                cout << b << endl;
  							white_turn = 0; // making it human's turn again
  						} else { // human's turn
  							cin >> game_cmd;
                
  							if (game_cmd == "resign") {
  								++white_score; // white earns a point
                  cout << "You resigned!" << endl;
                  cout << "computer" << player1_level << "(W) wins! Gets 1 point!" << endl;
  								white_turn = 1; // resetting so white can start in new game
  								break;
                } else if (game_cmd == "move") {
  								cin >> game_cmd_1 >> game_cmd_2;
                  
  								try { // game_cmd1 = initial pos, game_cmd2 = final pos, white_turn = whether white or black's turn
  									b.move(game_cmd_1, game_cmd_2, white_turn);
                    cout << endl;
                    cout << b << endl;
  								} catch (InvalidMove In) { // when the move is invalid
                    cout << "Try again." << endl << endl;
  									continue;
  								}
  								white_turn = 1; // turn changes
  							} else if (game_cmd == "undo") {
                  try {
                    b.undo();
                    cout << b;
                  } catch (InvalidMove in) {
                    cout << "you have reached the beginning of the game" << endl;
                  }
                  if (white_turn == 1) white_turn = 0; // turn changes
                  else white_turn = 1;
                } else if (game_cmd == "history") {
                  cout << endl;
                  b.printHistory(white_turn);
                  cout << endl;
                }
  						}
  						if (b.gameEnd()) { // always check if the game is over
  							if (b.winner() == Color::Black) {
  								++black_score; // black earns a point
  								cout << endl << "black_player wins! Gets 1 point!" << endl;
  							} else if (b.winner() == Color::White) {
  								white_score+=1; // white earns a point
  								cout << endl << "white_player wins! Gets 1 point!" << endl;
  							} else { // Stalemate or simply draw
	  							white_score+=0.5;
  								black_score+=0.5;
  								cout << "it's a draw! Players get 0.5 point each." << endl;
  							}
                white_turn = 1; // resetting so white can start in new game
  							break;
  						}  				
  					}
  				}
  			} else { // 2 computers
          b.setHumans(Color::White, false);
          b.setHumans(Color::Black, false);
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
              cout << endl;
              cout << b << endl;
  						white_turn = 0; // making it human's turn again
  					} else { // computer's turn
  						if (player2_level == 1) {
  							computer_1(b, Color::Black); // computer's move
  						} else if (player2_level == 2) {
  							computer_2(b, Color::Black);
  						} else if (player2_level == 3) {
  							computer_3(b, Color::Black);
  						} else { // computer level 4
  							computer_4(b, Color::Black);
  						}
              cout << endl;
              cout << b << endl;
  						white_turn = 1; // making it human's turn again
  					}
  					if (b.gameEnd()) { // always check if the game is over
  						if (b.winner() == Color::Black) {
  							++black_score; // black earns a point
  							cout << endl << "black_player wins! Gets 1 point!" << endl;
  						} else if (b.winner() == Color::White) {
  							++white_score; // white earns a point
  							cout << endl << "white_player wins! Gets 1 point!" << endl;
  						} else { // Stalemate or simply draw
  							white_score+=0.5;
  							black_score+=0.5;
  							cout << "it's a draw! Players get 0.5 point each." << endl;
  						}
              white_turn = 1; // resetting so white can start in new game
  						break;
  					}
  				}
  			}
  		}
  	}
  } catch (ios::failure &e) { // Any I/O failure quits
    score_print(white_score, black_score); // prints the scoreboard
	}
  return 0; // program ends
}
