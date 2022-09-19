#ifndef I_AGENT_H
#define I_AGENT_H

#include "Action.h"
#include <string>
#include "Board.h"

class IAgent {
    public:
        virtual BoardEntry id() const = 0;
        virtual std::string name() const = 0;
        virtual Action action(const Board board) const = 0;
        virtual void processGame(std::list<Board> boardSequence) = 0;
        bool operator==(const IAgent& other) const;
        BoardEntry opponentId() const {
            if(this->id() == X) {
                return O;
            } else {
                return X;
            }
        };
};

#endif /* I_AGENT_H */