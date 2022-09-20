#include "LearningAgent.h"

double Fitness::fitness() const {
    if (numberOfEncounters == 0) return 0;
    return summedValues / static_cast<double>(numberOfEncounters);
}

BoardEntry LearningAgent::id() const {
    return _id;
}

std::string LearningAgent::name() const {
    return _name;
}

#include <iostream>
Action LearningAgent::action(const Board board) const {
    std::list<BoardPosition> freePos = board.freePositions();
    auto position = freePos.begin();
    if (_explore && (double)rand()/(double)RAND_MAX < _explorationRate) {
        std::advance(position , floor((double)rand()/(double)RAND_MAX*(double)(freePos.size())));
        return Action(id(), *position);
    }
    Action bestAction(id(), *position);
    double maxFitness = -999.0;
    // choose action that maximises the value
    while(position != freePos.end()) {
        Action action(id(),*position);
        double fitness = _expectedValue(action, board);
        if (fitness > maxFitness) {
            maxFitness = fitness;
            bestAction = action;
        }
        position++;
    }
    return bestAction;
}

void LearningAgent::processGame(std::list<Board> boardSequence) {
    if (_learning) {
        double reward = boardSequence.back().reward(_id);
        // double valueOfNextState = _fitnessFunction[boardSequence.back().hash()];

        for (auto board = boardSequence.begin(); board != boardSequence.end(); board++) {
            Fitness& fit = _fitnessFunction[board->hash()];
            fit.numberOfEncounters++;
            fit.summedValues += static_cast<double>(reward);
        }

        // for (auto board = ++boardSequence.rbegin();
        //     board != boardSequence.rend(); board++) {
        //     double oldValue = _fitnessFunction[board->hash()];
        //     // std::cout << board->string() << std::endl;
        //     // double localReward = board->reward(_id);
        //     // double experimentalValue = localReward + _discountRate * valueOfNextState;
        //     // double updatedValue = oldValue + _learningRate
        //     //     * (experimentalValue - oldValue);
        //     double updatedValue = oldValue + (_learningRate * 
        //         (rewardTarget - oldValue));
        //     _fitnessFunction[board->hash()] = updatedValue;
        //     rewardTarget = updatedValue;
        // }

        // for (auto board = boardSequence.rbegin();
        //     board != boardSequence.rend(); ++board) {
        //     unsigned long hash = board->hash();
        //     //std::cout << board->string() << std::endl;
        //     double boardValue = board->reward(_id);
        //     double oldValue =  _fitnessFunction[hash];
        //     int idx = std::distance(board, boardSequence.rbegin());
        //     double discount = pow(_discountRate, idx);
        //     double discountedValue = discount * value;
        //     double newValue = oldValue + _learningRate
        //         * (discountedValue - oldValue);
        //     _fitnessFunction[hash] = newValue;
        // }
        // if (_learningRate > 0.01) {
        //     _learningRate -= 0.000001;
        // }
    }
}

// double LearningAgent::value(unsigned long hash) const {
//     return _fitnessFunction[hash];
// }

void LearningAgent::initialize() {
    // for (int hash = 0; hash < Board::NUMBER_OF_STATES; ++hash) {
    //     Board board(hash);
    //     _fitnessFunction[hash] = 0.5;
    //     if (board.isWinner(_id)) {
    //         _fitnessFunction[hash] = 1;
    //     }
    //     BoardEntry otherId;
    //     if (_id == X) {
    //         otherId = O;
    //     } else if (_id == O) {
    //         otherId = X;
    //     }
    //     if (board.isWinner(otherId)) {
    //         _fitnessFunction[hash] = 0;
    //     }
    // }
}

void LearningAgent::setExplorationRate(double rate) {
    _explorationRate = rate;
}

double LearningAgent::explorationRate() const {
    return _explorationRate;
}

void LearningAgent::setLearning(bool enable) {
    _learning = enable;
}

// double* LearningAgent::valueFunction() {
//     return _fitnessFunction;
// }

const Fitness* LearningAgent::fitnessFunction() const {
    return _fitnessFunction;
}


double LearningAgent::_expectedValue(Action localAction, Board localBoard) const {
    localBoard.move(localAction);
    return _fitnessFunction[localBoard.hash()].fitness();
}