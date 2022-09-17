#include "Board.h"

bool operator==(const BoardPosition& pos1, const BoardPosition& pos2) {
        return (pos1.row == pos2.row) && (pos1.col == pos2.col);
}
