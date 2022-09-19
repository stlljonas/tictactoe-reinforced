#ifndef TIC_TAC_TOE_BOARD
#define TIC_TAC_TOE_BOARD

#include <array>
#include <list>
#include <memory>
#include <iterator>
#include <assert.h>
#include "IAgent.h"
#include "Board.h"

enum GameState {
    START = 0,
    TURN_PLAYER = 1,
    WIN_PLAYER_1 = 2,
    WIN_PLAYER_2 = 3,
    TIE = 4,
    EXIT = 5,
};

enum Verbosity {
    SILENT = 0,
    NORMAL = 1,
    VERBOSE = 2
};

class TicTacToe {
    public:
        TicTacToe(IAgent* player1P, IAgent* player2P)
            : _player1P(player1P)
            , _player2P(player2P) {
            assert(player1P->id() != player2P->id());
            assert(_player1P != nullptr && _player2P != nullptr);
        }
        std::string string() const;
        const Board board() const;
        std::list<Action> possibleActions(const IAgent& player) const;
        const IAgent* player1P() const;
        const IAgent* player2P() const;
        void game();
        void start();
        void start(const IAgent& startingPlayer);
        void setVerbosity(Verbosity verbosity);
        int numberOfGamesWon(const IAgent& player) const;
        int numberOfGamesPlayed() const;
        double winLossRatio(const IAgent& player) const;
        void reset();
        void reset(IAgent* player1P, IAgent* player2P);
        void setLearning(bool input);

    private:
        Board _board = Board();
        std::list<Board> _boardSequence;
        GameState _gameState = GameState::START;
        IAgent* _player1P;
        IAgent* _player2P; 
        BoardEntry _currentPlayerId;
        Verbosity _verbosity = Verbosity::SILENT;
        int _numberOfGamesWonPlayer1 = 0;
        int _numberOfGamesWonPlayer2 = 0;
        int _numberOfGamesPlayed = 0;
        int _numberOfInvalidInputs = 0;
        const int _maxInvalidInputs = 3;
        bool _learning = true;
        void _play(Action act);
        void _gameOver();
        bool _isWinner(BoardEntry id) const;
        bool _isValidAction(Action act) const;
        Action _nextAction() const;
        BoardEntry _nextPlayerId(BoardEntry currentPlayerId) const;
        void _setPosition(BoardEntry id, int row, int col);
        BoardEntry _idToBoardEntry(int id) const;
        IAgent& _idToPlayer(BoardEntry id) const;
};

#endif /* TIC_TAC_TOE_BOARD */
