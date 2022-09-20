#ifndef LEARNING_AGENT_H
#define LEARNING_AGENT_H

#include "IAgent.h"
#include <math.h>

struct Fitness {
    int numberOfEncounters = 0;
    double summedValues = 0;
    double fitness() const;
};

class LearningAgent : public IAgent {
    public:
        LearningAgent(BoardEntry id, std::string name = "LearningAgent") 
        : _id(id),
        _name(name) {};
        BoardEntry id() const override;
        std::string name() const override;
        Action action(const Board board) const override;
        void processGame(std::list<Board> boardSequence) override;
        void initialize();
        //double value(unsigned long hash) const;
        double explorationRate() const;
        void setExplorationRate(double explorationRate);
        void setLearning(bool enable);
        const Fitness* fitnessFunction() const;


    private:
        // const double _discountRate = 0.9;
        double _learningRate = 0.7;
        double _explorationRate = 0.5;
        bool _explore = true;
        bool _learning = true;
        const BoardEntry _id;
        const std::string _name;
        Fitness _fitnessFunction[Board::NUMBER_OF_STATES] = {};
        double _expectedValue(Action action, Board board) const;
};

#endif /* LEARNING_AGENT_H */