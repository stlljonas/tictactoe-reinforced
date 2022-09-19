#include "LearningAgent.h"

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
        std::advance(position , round((double)rand()/(double)RAND_MAX*(double)(freePos.size()-1) - 0.5));
        return Action(id(), *position);
    }
    Action bestAction(id(), *position);
    double maxValue = -1.0;
    // choose action that maximises the value
    while(++position != freePos.end()) {
        Action localAction(id(),*position);
        double localValue = _expectedValue(localAction, board);
        if (localValue > maxValue) {
            maxValue = localValue;
            bestAction = localAction;
        }
    }
    return bestAction;
}

void LearningAgent::processGame(std::list<Board> boardSequence) {
    auto board = boardSequence.rbegin();
    double value = board->reward(id(), opponentId());
    unsigned long hash = board->hash();
    _valueFunction[hash] = _learningRate * (value - _valueFunction[hash]);
    board++;

    for (; board != boardSequence.rend(); ++board) {
        unsigned long hash = board->hash();
        value *= _discountRate;
        _valueFunction[hash] = _learningRate * (value - _valueFunction[hash]);
    }
}

double LearningAgent::value(unsigned long hash) const {
    return _valueFunction[hash];
}

void LearningAgent::initialize() {
    for (int hash = 0; hash < Board::NUMBER_OF_STATES; ++hash) {
        Board board(hash);
        _valueFunction[hash] = board.reward(_id, this->opponentId());
    }
}

void LearningAgent::setExplore(bool enable) {
    _explore = enable;
}

double LearningAgent::_expectedValue(Action localAction, Board localBoard) const {
    localBoard.move(localAction);
    return _valueFunction[localBoard.hash()];
}