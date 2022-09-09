#ifndef TIC_TAC_TOE_BOARD
#define TIC_TAC_TOE_BOARD

#include "IModel.h"
#include <array>

enum BoardEntry {
    NONE = 0, AGENT = 1, OPPONENT = 2
};

class TicTacToeBoard : public IModel {
    public:
        std::string toString() const override;
    private:
        std::array<std::array<BoardEntry, 3>, 3> _state = {};
};

#endif /* TIC_TAC_TOE_BOARD */