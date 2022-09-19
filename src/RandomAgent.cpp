#include "RandomAgent.h"
#include <random>

BoardEntry RandomAgent::id() const {
    return _id;
}

std::string RandomAgent::name() const {
    return _name;
}

Action RandomAgent::action(const Board board) const {
    std::list<BoardPosition> freePos = board.freePositions();
    int randomIdx = round(((double)rand()/(double)RAND_MAX)*9.0 - 0.5);
    if (randomIdx < 0) randomIdx = 0;
    if (randomIdx > 8) randomIdx = 8;
    auto it = freePos.begin();
    std::advance(it, randomIdx);
    return Action(id(), *it); // naive approach
}