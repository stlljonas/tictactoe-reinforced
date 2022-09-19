#include "TicTacToe.h"
#include "IAgent.h"
#include "RandomAgent.h"
#include "RealAgent.h"
#include "LearningAgent.h"
#include "Board.h"
#include <iostream>
#include <random>
#include <time.h>
#include <cmath>
#include <algorithm>
#include <iterator>

const int nTrainingEpochs = 1000;
const int nGamesPerEpoch = 100;
const int nValidationGames = 10000;

LearningAgent learner = LearningAgent(O, "LEARNER");
RealAgent user = RealAgent(X, "USER");
RandomAgent gambler = RandomAgent(X, "RANDOM_AGENT");
LearningAgent adverserialLearner = LearningAgent(X, "ADVERSERIAL");
TicTacToe ttt = TicTacToe(&learner, &adverserialLearner);
TicTacToe tttValidate = TicTacToe(&learner, &gambler);
TicTacToe tttTest = TicTacToe(&learner, &user);

int main (int argc, char *argv[]) {
    std::srand(time(0));
    learner.initialize();
    adverserialLearner.initialize();

    //double rate = learner.explorationRate();
    // learner.setExplorationRate(0.0);
    learner.setLearning(false);
    tttValidate.reset();
    for (int g = 0; g < nValidationGames; ++g) {
        tttValidate.game();
    }

    std::cout << "EPOCH " << 0 << "| Approximated win ratio against random player: "
        << static_cast<double>(tttValidate.numberOfGamesWon(learner))
        / (static_cast<double>(tttValidate.numberOfGamesWon(learner))
        + static_cast<double>(tttValidate.numberOfGamesWon(gambler)))
        << std::endl;

    // Training
    std::cout << "Training " << ttt.player1P()->name()
        << " against " << ttt.player2P()->name() << std::endl;
    
    double lastValuefunction[Board::NUMBER_OF_STATES];
    for (int i = 0; i < Board::NUMBER_OF_STATES; ++i) {
        lastValuefunction[i] = learner.valueFunction()[i];
    }

    for (int e = 1; e < nTrainingEpochs; ++e) {
        // learner.setExplorationRate(rate);
        learner.setLearning(true);
        for (int g = 0; g < nGamesPerEpoch; ++g) {
            ttt.game();
        }
        // rate = learner.explorationRate();
        // learner.setExplorationRate(0.0);
        learner.setLearning(false);
        tttValidate.reset();
        for (int g = 0; g < nValidationGames; ++g) {
            tttValidate.game();
        }
        double ssd = 0;
        for (int i = 0; i < Board::NUMBER_OF_STATES; ++i) {
            ssd += pow(lastValuefunction[i] - learner.valueFunction()[i], 2);
        }
        for (int i = 0; i < Board::NUMBER_OF_STATES; ++i) {
            lastValuefunction[i] = learner.valueFunction()[i];
        }

        std::cout << "EPOCH " << e << "| Approximated win ratio against random player: "
            << static_cast<double>(tttValidate.numberOfGamesWon(learner))
            / (static_cast<double>(tttValidate.numberOfGamesWon(learner))
            + static_cast<double>(tttValidate.numberOfGamesWon(gambler)))
            << " | change w.r.t. last epoch : " << ssd << std::endl;
    }
    tttTest.setVerbosity(Verbosity::NORMAL);
    while(1) {
        tttTest.game();
    }
}