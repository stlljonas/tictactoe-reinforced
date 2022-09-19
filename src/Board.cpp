#include "Board.h"
#include <math.h>
#include "IAgent.h"
#include <algorithm>

std::string Board::string() const {
    
    // e.g.
    // +---+---+---+
    // | X | O |   |
    // +---+---+---+
    // |   | X |   |
    // +---+---+---+
    // | O |   | X |
    // +---+---+---+

    std::string boardString = "+---+---+---+";
    for (int row = 0; row < 3; ++row) {
        boardString += "\n|";
        for (int col = 0; col < 3; ++col) {
            boardString += " ";
            boardString += boardEntryToString(array[row][col]);
            boardString += " ";
            boardString += "|";
        }
        boardString += "\n+---+---+---+";
    }
    return boardString;
}

std::string Board::boardEntryToString(BoardEntry entry) const {
        switch(entry) {
            case(BoardEntry::None):
                return " ";
            case(X):
                return "X";
            case(O):
                return "O";
            default:
                return " ";
        }
    }


std::list<BoardPosition> Board::freePositions() const {
    std::list<BoardPosition> posList = {};
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (array[row][col] == 0) {
                posList.push_back(BoardPosition(row,col));
            }
        }
    }
    return posList;
}

bool Board::isFreePosition(BoardPosition pos) const {
    const std::list<BoardPosition> posList = freePositions();
    return (std::find(posList.begin(),posList.end(), pos) != posList.end());
}

void Board::reset() {
    array = {};
}

bool operator==(const BoardPosition& pos1, const BoardPosition& pos2) {
        return (pos1.row == pos2.row) && (pos1.col == pos2.col);
}

bool Board::isWinner(const BoardEntry entry) const {
        for(int i = 0; i < 3; ++i) {
        if (array[0][i] == array[1][i]
            && array[0][i] == array[2][i]
            && array[0][i] == entry) {
            return true;
        }
    }
    // check vertical
    for (int i = 0; i < 3; ++i) {
        if (array[i][0] == array[i][1]
            && array[i][0] == array[i][2]
            && array[i][0] == entry) {
            return true;
        }
    }
    // check diagonal
    if (array[0][0] == array[1][1]
        && array[0][0] == array[2][2]
        && array[0][0] == entry) {
        return true;
    
    }
    if (array[0][2] == array[1][1]
        && array[0][2] == array[2][0]
        && array[0][2] == entry) {
        return true;
    }
    return false;
}

double Board::reward(const BoardEntry& playerId) const {
    BoardEntry opponentId;
    if (playerId == X) {
        opponentId = O;
    } else if (playerId == O) {
        opponentId = X;
    }
    if (isWinner(playerId)) {
        return 1.0;
    } else if (isWinner(opponentId)) {
        return 0.0;
    // } else if (freePositions().size() == 0) {
    //     return 0.5;
    } else {
        return 0.0;
    }
}

void Board::move(Action action) {
    array[action.pos.row][action.pos.col] = action.id;
}

const BoardEntry& Board::operator[](int index) const {
    return array.data()[index/3].data()[index%3]; // [index/3][index%3];
}

unsigned long Board::hash() const {
    unsigned long hash = 0;
    for (unsigned long field = 0; field < Board::NUMBER_OF_FIELDS; ++field) {
        unsigned long mutliplier = 0;
        if ((*this)[field] == X) {
            mutliplier = 1;
        } else if ((*this)[field] == O) {
            mutliplier = 2;
        }
        hash += pow(3, field) * mutliplier;
    }
    return hash;
}

void Board::construct(unsigned long hash) {
    for (int field = 0; field < NUMBER_OF_FIELDS; ++field) {
        array[field/3][field%3] = BoardEntry(hash%3);
        hash /= 3;
    }
}