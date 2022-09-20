#include "RealAgent.h"
#include <iostream>

BoardEntry RealAgent::id() const {
    return _id;
}

std::string RealAgent::name() const {
    return _name;
}

Action RealAgent::action(const Board board) const {
    while(1) {
        std::cout << board.stringWithNumbers() << std::endl;
        std::cout << "Type a number between 1 and 9 and press Enter to select one of the free positions.\n"
            << "(numbered left to right and top to bottom): ";
        int selection = 0;
        std::cin >> selection;
        if (std::cin.fail()) {
            std::cout << "ERROR: Invalid Input!\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        selection -= 1;
        if (selection < 0 || selection > 8) {
            selection = -1;
            continue;
        }
        BoardPosition selectedPosition{selection/3, selection%3};
        if (not board.isFreePosition(selectedPosition)) {
            std::cout << "ERROR: Invalid Input!\n";
            selection = -1;
            continue;
        }
        return Action{id(), selectedPosition};
    }
}
