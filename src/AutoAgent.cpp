#include "AutoAgent.h"

int AutoAgent::id() const {
    return _id;
}

std::string AutoAgent::name() const {
    return _name;
}

Action AutoAgent::nextAction(const Board board) const {
    std::list<BoardPosition> freePos = board.freePositions();
    return Action(id(), freePos.front()); // naive approach
}