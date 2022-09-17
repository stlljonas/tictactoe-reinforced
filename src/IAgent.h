#ifndef I_AGENT_H
#define I_AGENT_H

#include "Board.h"
#include "Action.h"

class IAgent {
    public:
        virtual int id() const = 0;
        virtual std::string name() const = 0;
        virtual Action nextAction(const Board board) const = 0;
};

#endif /* I_AGENT_H */