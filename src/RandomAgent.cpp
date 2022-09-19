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
    const int nChoices = freePos.size();
    int randomIdx = floor(((double)rand()/(double)RAND_MAX)*(nChoices));
    // if (randomIdx < 0) randomIdx = 0;
    // if (randomIdx >= nChoices) randomIdx = nChoices-1;
    auto it = freePos.begin();
    std::advance(it, randomIdx);
    return Action(_id, *it); // naive approach
}