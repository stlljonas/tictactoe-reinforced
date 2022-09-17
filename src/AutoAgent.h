#ifndef AUTO_AGENT_H
#define AUTO_AGENT_H

#include "IAgent.h"

class AutoAgent : public IAgent {
    public:
        AutoAgent(int id, std::string name = "AutoAgent") 
        : _id(id),
        _name(name) {};
        int id() const override;
        std::string name() const override;
        Action nextAction(const Board board) const override;

    private:
        const int _id;
        const std::string _name;
};

#endif /* AUTO_AGENT_H */