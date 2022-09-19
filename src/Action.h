#ifndef ACTION_H
#define ACTION_H

#include "BoardEntry.h"

struct Action {
    Action(BoardEntry id_, BoardPosition pos_)
        : id(id_), pos(pos_) {}
    BoardEntry id;
    BoardPosition pos;
};

#endif /* ACTION_H */