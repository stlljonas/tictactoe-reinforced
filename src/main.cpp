#include "TicTacToe.h"
#include "IAgent.h"
#include "AutoAgent.h"
#include "RealAgent.h"
#include <iostream>

int main (int argc, char *argv[]) {
    // we need a board that has the ttt state and all the
    // methods needed to play the game
    // we will have TWO agents that have policie and interact
    // with the board

    RealAgent player1 = RealAgent(1);
    AutoAgent player2 = AutoAgent(2);
    TicTacToe ttt = TicTacToe(player1, player2);

    while(ttt.gameState() != GameState::EXIT){
        switch(ttt.gameState()) {
            case GameState::START: {
                std::cout << "Tic Tac Toe!\n";
                 std::cout << "Type s to start!\n"
                << "Type e to exit.\n"
                << "Press Enter to confirm." << std::endl;
                std::string selection;
                std::cin >> selection;
                if (selection == "s") {
                    ttt.start(player1);
                } else if (selection == "e") {
                    std::cout << "Terminating.\n";
                    ttt.exit();
                } else {
                    std::cout << "ERROR: Invalid Input!\n";
                }
                break;
            }
            case GameState::TURN_PLAYER: {
                std::cout << ttt.string() << std::endl;
                if (ttt.currentPlayerId() == player1.id()) {
                    ttt.round(player1.nextAction(ttt.board()));  
                } else if (ttt.currentPlayerId() == player2.id()) {
                    ttt.round(player2.nextAction(ttt.board()));  
                }
                break;
            }
            case GameState::WIN_PLAYER_1: {
                std::cout << "\n\n" << player1.name() << " won!\n"
                    << "Press enter to continue..\n\n\n";
                std::cin;
                ttt.reset();
            }
            case GameState::WIN_PLAYER_2: {
                std::cout << "\n\n" << player2.name() << " won!\n"
                    << "Press enter to continue..\n\n\n";
                std::cin;
                ttt.reset();
                break;
            }
            case GameState::TIE:
                std::cout << "\n\n" << "There is a tie!\n"
                    << "Press enter to continue..\n\n\n";
                std::cin;
                ttt.reset();
                break;
            default:
                ttt.exit();
                break;
        }
    }
}