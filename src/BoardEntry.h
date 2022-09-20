#ifndef BOARD_ENTRY_H
#define BOARD_ENTRY_H

enum BoardEntry {
    None = 0,
    X = 1,
    O = 2
};

#define X BoardEntry::X
#define O BoardEntry::O
#define No BoardEntry::None

struct BoardPosition {
    BoardPosition(int row_, int col_)
        : row(row_), col(col_) {}
    friend bool operator==(const BoardPosition& pos1, const BoardPosition& pos2);
    int row;
    int col;
};

#endif /* BOARD_ENTRY_H */