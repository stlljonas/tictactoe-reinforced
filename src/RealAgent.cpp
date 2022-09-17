#include "RealAgent.h"
#include <iostream>

int RealAgent::id() const {
    return _id;
}

std::string RealAgent::name() const {
    return _name;
}

Action RealAgent::nextAction(const Board board) const {
    std::list<BoardPosition> freePos = board.freePositions();
    int selection = 0;
    while (selection < 1 || selection > freePos.size()) {
        std::cout << "Type a number between 1 and " << freePos.size()
            << " and press Enter to select one of the " << freePos.size() << " free positions.\n"
            << "(Numbered left to right and top to bottom.):" << std::endl;
        std::cin >> selection;
        std::cout << "You selected free position " << selection << std::endl;
        if (selection < 1 || selection > freePos.size()) {
            std::cout << "ERROR: Invalid Input!\n";
        } else {
            auto it = freePos.begin();
            std::advance(it, selection-1);
            return Action{id(), *it};
        }
    }
}