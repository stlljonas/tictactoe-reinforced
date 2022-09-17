#ifndef TIC_TAC_TOE_BOARD
#define TIC_TAC_TOE_BOARD

#include <array>
#include <list>
#include <memory>
#include <iterator>
#include "IAgent.h"

enum GameState {
    START = 0,
    TURN_PLAYER = 1,
    WIN_PLAYER_1 = 2,
    WIN_PLAYER_2 = 3,
    TIE = 4,
    EXIT = 5,
};

class TicTacToe {
    public:
        TicTacToe(IAgent& player1, IAgent& player2)
            : _player1(player1)
            , _player2(player2) {}
        std::string string() const;
        const Board board() const;
        const GameState gameState() const;
        float reward(const IAgent& player) const;
        std::list<Action> possibleActions(const IAgent& player) const;
        int currentPlayerId() const;
        void start();
        void start(const IAgent& startingPlayer);
        void reset();
        void round(Action act);
        void gameOver();
        void exit();

    private:
        Board _board = Board();
        GameState _gameState = GameState::START;
        IAgent& _player1;
        IAgent& _player2; 
        int _currentPlayerId;
        int _moveNumber = 0;
        bool _isWinner(const int id) const;
        bool _isValidAction(Action act) const;
        int _nextPlayerId(int currentPlayerId) const;
        void _setPosition(int id, int row, int col);
        BoardEntry _idToBoardEntry(int id) const;
        IAgent& _idToPlayer(int id) const;
};

#endif /* TIC_TAC_TOE_BOARD */
