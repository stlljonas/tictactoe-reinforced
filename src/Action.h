#ifndef ACTION_H
#define ACTION_H

#include "Board.h"

struct Action {
    Action(int id_, BoardPosition pos_)
        : id(id_), pos(pos_) {}
    int id;
    BoardPosition pos;
};

#endif /* ACTION_H */