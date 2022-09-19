#include "TicTacToe.h"
#include "IAgent.h"
#include "RandomAgent.h"
#include "RealAgent.h"
#include "LearningAgent.h"
#include "Board.h"
#include <iostream>
#include <random>

const int nTrainingGames = 1000000;
const int nValidationGames = 10000;

LearningAgent learner = LearningAgent(O, "LEARNER");
RealAgent user = RealAgent(X, "USER");
RandomAgent gambler = RandomAgent(X, "RANDOM_AGENT");
LearningAgent adverserialLearner = LearningAgent(X, "ADVERSERIAL");
TicTacToe ttt = TicTacToe(&learner, &adverserialLearner);


int main (int argc, char *argv[]) {
        
    learner.initialize();
    adverserialLearner.initialize();

    // Training
    std::cout << "Training " << ttt.player1P()->name()
        << " against " << ttt.player2P()->name() << std::endl;

    ttt.game();
    std::cout << "Win ratio " << learner.name() << ": "
                << ttt.winLossRatio(learner) << std::endl;
    while(ttt.numberOfGamesPlayed() < nTrainingGames) {
        ttt.game();
        if ((ttt.numberOfGamesPlayed()%(nTrainingGames/20)) == 0) {
            std::cout << "Win ratio " << learner.name() << ": "
                << ttt.winLossRatio(learner) << std::endl;
        }
    }

    // Validating
    std::cout << "Validating " << learner.name()
        << " against " << gambler.name() << ":\n";

    ttt.reset(&learner, &gambler);
    ttt.setLearning(false);

    learner.setExplore(false);

    while (ttt.numberOfGamesPlayed() < nValidationGames) {
        ttt.game();
        if ((ttt.numberOfGamesPlayed()%(nValidationGames/25)) == 0) {
            std::cout << ".";
            std::cout.flush();
        }
    }
    std::cout << std::endl;

    std::cout << "Win ratio " << learner.name() << ": "
        << ttt.winLossRatio(learner) << std::endl;

    ttt.reset(&learner, &user);
    ttt.setVerbosity(Verbosity::NORMAL);

    while(1) {
        int a;
        ttt.game();
    }

    // while(ttt.gameState() != GameState::EXIT){
    //     switch(ttt.gameState()) {
    //         case GameState::START: {
    //             std::cout << "game "  << numberOfGames << " tally: "
    //                 << "Player1/Player2 = " << static_cast<double>(numberOfWinsPlayer1)
    //                 / static_cast<double>(numberOfWinsPlayer2) << std::endl;
    //             if (numberOfGames >= maxNumberOfTrainingGames) {
    //                 std::cout << "Player 1 won " << numberOfWinsPlayer1 << " times.\n"; 
    //                 std::cout << "Player 2 won " << numberOfWinsPlayer2 << " times.\n"; 
    //                 std::cout << "Player1/Player2 = " << static_cast<double>(numberOfWinsPlayer1)
    //                     / static_cast<double>(numberOfWinsPlayer2) << std::endl;
    //                 ttt.exit();
    //             } else {
    //                 bool randomBool = round((double)rand()/(double)RAND_MAX);
    //                 if (randomBool) {
    //                     ttt.start(player1);
    //                 } else {
    //                     ttt.start(player2);
    //                 }
    //                 //std::cout << ttt.string() << std::endl;
    //             }
    //             break;
    //         }
    //         case GameState::TURN_PLAYER: {
    //             if (ttt.currentPlayerId() == player1.id()) {
    //                 ttt.round(player1.action(ttt.board()));  
    //             } else if (ttt.currentPlayerId() == player2.id()) {
    //                 ttt.round(player2.action(ttt.board()));  
    //             }
    //             // std::cout << ttt.string() << std::endl;
    //             break;
    //         }
    //         case GameState::WIN_PLAYER_1: {
    //             //std::cout << ttt.string() << std::endl;
    //             numberOfWinsPlayer1++;
    //             numberOfGames++;
    //             ttt.gameOver();
    //             // std::cout << "\n\n" << player1.name() << " won!\n\n\n";
    //             break;
    //         }
    //         case GameState::WIN_PLAYER_2: {
    //             //std::cout << ttt.string() << std::endl;
    //             numberOfWinsPlayer2++;
    //             numberOfGames++;
    //             // std::cout << "\n\n" << player2.name() << " won!\n\n\n";
    //             ttt.gameOver();
    //             break;
    //         }
    //         case GameState::TIE:
    //             //std::cout << ttt.string() << std::endl;
    //             // std::cout << "\n\n" << "There was a tie!\n\n\n";
    //             ttt.gameOver();
    //             break;
    //         default:
    //             ttt.exit();
    //             break;
    //     }
    // }

    // player2.setExplore(false);
    // int numberOfWinsUser = 0;
    // numberOfWinsPlayer2 = 0;
    // // play against user
    // RealAgent player3 = RealAgent(X);
    // TicTacToe tt2 = TicTacToe(player3, player2);
    // while(tt2.gameState() != GameState::EXIT){
    //     switch(tt2.gameState()) {
    //         case GameState::START: {
    //             std::cout << "game "  << numberOfGames << std::endl;
    //             // if (numberOfGames >= maxNumberOfGames) {
    //             //     std::cout << "User won " << numberOfWinsUser << " times.\n"; 
    //             //     std::cout << "Player 2 won " << numberOfWinsPlayer2 << " times.\n"; 
    //             //     std::cout << "User/Player2 = " << static_cast<double>(numberOfWinsUser)
    //             //         / static_cast<double>(numberOfWinsPlayer2) << std::endl;
    //             //     tt2.exit();
    //             // } else {
    //                 bool randomBool = round((double)rand()/(double)RAND_MAX);
    //                 if (randomBool) {
    //                     tt2.start(player3);
    //                 } else {
    //                     tt2.start(player2);
    //                 }
    //                 std::cout << tt2.string() << std::endl;
    //             // }
    //             break;
    //         }
    //         case GameState::TURN_PLAYER: {
    //             if (tt2.currentPlayerId() == player3.id()) {
    //                 tt2.round(player3.action(tt2.board()));  
    //             } else if (tt2.currentPlayerId() == player2.id()) {
    //                 tt2.round(player2.action(tt2.board()));  
    //             }
    //             std::cout << tt2.string() << std::endl;
    //             break;
    //         }
    //         case GameState::WIN_PLAYER_1: {
    //             std::cout << tt2.string() << std::endl;
    //             numberOfWinsUser++;
    //             numberOfGames++;
    //             tt2.gameOver();
    //             std::cout << "\n\n" << player3.name() << " won!\n\n\n";
    //             break;
    //         }
    //         case GameState::WIN_PLAYER_2: {
    //             std::cout << tt2.string() << std::endl;
    //             numberOfWinsPlayer2++;
    //             numberOfGames++;
    //             std::cout << "\n\n" << player2.name() << " won!\n\n\n";
    //             tt2.gameOver();
    //             break;
    //         }
    //         case GameState::TIE:
    //             std::cout << tt2.string() << std::endl;
    //             std::cout << "\n\n" << "There was a tie!\n\n\n";
    //             tt2.gameOver();
    //             break;
    //         default:
    //             tt2.exit();
    //             break;
    //     }
    // }
}