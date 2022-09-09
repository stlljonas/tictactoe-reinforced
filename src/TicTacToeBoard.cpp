#include "TicTacToeBoard.h"

std::string boardEntryToString(BoardEntry entry) {
    switch(entry) {
        case(BoardEntry::NONE):
            return " ";
        case(BoardEntry::AGENT):
            return "X";
        case(BoardEntry::OPPONENT):
            return "O";
        default:
            return " ";
    }
}

std::string TicTacToeBoard::toString() const {
    
    // +---+---+---+
    // | a | b | c |
    // +---+---+---+
    // | d | e | f |
    // +---+---+---+
    // | g | h | i |
    // +---+---+---+

    std::string boardString = "+---+---+---+";
    for (int row = 0; row < 3; row++) {
        boardString += "\n|";
        for (int col = 0; col < 3; col++) {
            boardString += " ";
            boardString += boardEntryToString(_state[row][col]);
            boardString += " ";
            boardString += "|";
        }
        boardString += "\n+---+---+---+";
    }
    return boardString;
}