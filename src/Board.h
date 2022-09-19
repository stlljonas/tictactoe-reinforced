#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <array>
#include "BoardEntry.h"
#include "Action.h"

struct Board {
    Board() = default;
    Board(unsigned long hash) {
        this->construct(hash);
    }
    std::string string() const;
    std::list<BoardPosition> freePositions() const;
    bool isFreePosition(BoardPosition pos) const;
    bool isWinner(const BoardEntry entry) const;
    void reset();
    const BoardEntry& operator[](int index) const;
    std::array<std::array<BoardEntry, 3>, 3> array = {};
    std::string boardEntryToString(BoardEntry entry) const;
    double reward(const BoardEntry& player, const BoardEntry& opponent) const;
    void move(Action action);
    const static int NUMBER_OF_FIELDS = 9;
    const static int NUMBER_OF_STATES = 19683;    //  {None, X, O} ^ 9 fields on the board
    unsigned long hash() const;
    void construct(unsigned long hash);
};

#endif /* BOARD_H */