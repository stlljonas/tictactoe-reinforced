#include "TicTacToeBoard.h"
#include <iostream>

int main (int argc, char *argv[]) {
    TicTacToeBoard board = TicTacToeBoard();
    std::cout << board.toString() << std::endl;
}