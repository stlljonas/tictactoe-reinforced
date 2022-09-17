#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <array>

enum BoardEntry {
    None = 0,
    X = 1,
    O = 2
};

#define X BoardEntry::X
#define O BoardEntry::O

struct BoardPosition {
    BoardPosition(int row_, int col_)
        : row(row_), col(col_) {}
    friend bool operator==(const BoardPosition& pos1, const BoardPosition& pos2);
    int row;
    int col;
};

struct Board {
    std::string string() const;
    std::list<BoardPosition> freePositions() const;
    bool isFreePosition(BoardPosition pos) const;
    void reset();
    std::array<std::array<BoardEntry, 3>, 3> array = {};
    std::string boardEntryToString(BoardEntry entry) const;
};

#endif /* BOARD_H */