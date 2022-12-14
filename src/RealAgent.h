#ifndef REAL_AGENT_H
#define REAL_AGENT_H

#include "IAgent.h"

class RealAgent : public IAgent {
    public:
        RealAgent(BoardEntry id, std::string name = "Anonymous")
        : _id(id),
        _name(name) {};
        BoardEntry id() const override;
        std::string name() const override;
        Action action(const Board board) const override;
        void processGame(std::list<Board> boardSequence) override {};
    private:
        const BoardEntry _id;
        const std::string _name;
};

#endif /* REAL_AGENT_H */