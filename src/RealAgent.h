#ifndef REAL_AGENT_H
#define REAL_AGENT_H

#include "IAgent.h"

class RealAgent : public IAgent {
    public:
        RealAgent(int id, std::string name = "Anonymous")
        : _id(id),
        _name(name) {};
        int id() const override;
        std::string name() const override;
        Action nextAction(const Board board) const override;
    private:
        const int _id;
        const std::string _name;
};

#endif /* REAL_AGENT_H */