#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

#include "IAgent.h"

class RandomAgent : public IAgent {
    public:
        RandomAgent(BoardEntry id, std::string name = "RandomAgent") 
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

#endif /* RANDOM_AGENT_H */