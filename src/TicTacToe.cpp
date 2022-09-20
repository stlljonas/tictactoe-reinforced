#include "TicTacToe.h"
#include <algorithm>
#include <cmath>
#include <iostream>

std::string TicTacToe::string() const {
    return _board.string();
}

const Board TicTacToe::board() const {
    return _board;
}

std::list<Action> TicTacToe::possibleActions(const IAgent& agent) const {
    std::list<BoardPosition> posList = _board.freePositions();
    std::list<Action> actionList;
    const BoardEntry id = agent.id();
    for (auto it = posList.begin(); it != posList.end(); ++it) {
        actionList.push_back(Action(id, *it));
    }
    return actionList;
}

const IAgent* TicTacToe::player1P() const {
    return _player1P;
}

const IAgent* TicTacToe::player2P() const {
    return _player2P;
}

void TicTacToe::game() {
    while(_gameState != GameState::EXIT) {
        switch (_gameState) {
            case GameState::START: {
                // randomly select starting player
                bool randomBool = std::round((double)rand()/(double)RAND_MAX);
                if (randomBool) {
                    start(_player1P);
                } else {
                    start(_player2P);
                }
                if (_verbosity >= Verbosity::NORMAL) {
                    std::cout << "Starting New Game.\n";
                    std::cout << string() << std::endl;
                }
                break;
            }
            case GameState::TURN_PLAYER: {
                _play(_nextAction());
                if (_verbosity >= Verbosity::NORMAL) {
                    std::cout << _currentPlayerP->name() << "'s turn:\n";
                    std::cout << string() << std::endl;
                }
                break;
            }
            case GameState::WIN_PLAYER_1: {
                _numberOfGamesWonPlayer1++;
                _numberOfGamesPlayed++;
                if (_verbosity >= Verbosity::NORMAL) {
                    std::cout << "\n\n" << _player1P->name() << " won!\n\n\n" << std::endl;
                }
                _gameOver();
                break;
            }
            case GameState::WIN_PLAYER_2: {
                _numberOfGamesWonPlayer2++;
                _numberOfGamesPlayed++;
                if (_verbosity >= Verbosity::NORMAL) {
                    std::cout << "\n\n" << _player2P->name() << " won!\n\n\n" << std::endl;
                }
                _gameOver();
                break;
            }
            case GameState::TIE: {
                _numberOfGamesPlayed++;
                if (_verbosity >= Verbosity::NORMAL) {
                    std::cout << "\n\n" << "There was a tie!\n\n\n" << std::endl;
                }
                _gameOver();
                break;
            }
            default:
                _gameState = GameState::EXIT;
                break;
        }
    }
    _gameState = GameState::START;
}

void TicTacToe::start() {
    start(_player1P);
}

void TicTacToe::start(IAgent* startingPlayer) {
    _board.reset();
    _boardSequence.clear();
    _boardSequence.push_back(_board);
    _currentPlayerP = startingPlayer;
    _numberOfInvalidInputs = 0;
    _gameState = GameState::TURN_PLAYER;

}

void TicTacToe::_play(Action act) {
    if (not _isValidAction(act)) {
        if (_numberOfInvalidInputs >= _maxInvalidInputs) {
            _gameState = GameState::EXIT;
        }
        _numberOfInvalidInputs++;
        return; // retry
    } else {
        _numberOfInvalidInputs = 0;
        _board.move(act);
        _boardSequence.push_back(_board);
        _currentPlayerP = _nextPlayerP(_currentPlayerP);
    }
    if (_isWinner(_player1P->id())) {
        _gameState = GameState::WIN_PLAYER_1;
    } else if (_isWinner(_player2P->id())) {
        _gameState = GameState::WIN_PLAYER_2;
    } else if (_board.freePositions().size() == 0) {
        _gameState = GameState::TIE;
    }
}

void TicTacToe::_gameOver() {
    _player1P->processGame(_boardSequence);
    _player2P->processGame(_boardSequence);
    _gameState = GameState::EXIT;
}

void TicTacToe::setVerbosity(Verbosity verbosity) {
    _verbosity = verbosity;
}

int TicTacToe::numberOfGamesWon(const IAgent& player) const {
    if (player == *_player1P) {
        return _numberOfGamesWonPlayer1;
    } else if (player == *_player2P) {
        return _numberOfGamesWonPlayer2;
    } else {
        return 0;
    }
}

int TicTacToe::numberOfGamesPlayed() const {
    return _numberOfGamesPlayed;
}

double TicTacToe::winLossRatio(const IAgent& player) const {
    int numerator = 0;
    int denominator = 1;
    if (player == *_player1P) {
        numerator = numberOfGamesWon(*_player1P);
        denominator = numberOfGamesWon(*_player2P);
    } else if (player == *_player2P) {
        numerator = numberOfGamesWon(*_player2P);
        denominator = numberOfGamesWon(*_player1P);
    }
    return static_cast<double>(numerator)
        / static_cast<double>(denominator);
}

void TicTacToe::reset() {
    _numberOfGamesWonPlayer1 = 0;
    _numberOfGamesWonPlayer2 = 0;
    _numberOfGamesPlayed = 0;
    _numberOfInvalidInputs = 0;
    _boardSequence.clear();
    _board.reset();
}

void TicTacToe::reset(IAgent* player1P, IAgent* player2P) {
    assert(_player1P != nullptr && _player2P != nullptr);
    _player1P = player1P;
    _player2P = player2P;
    reset();
}

bool TicTacToe::_isValidAction(Action act) const {
    return _board.isFreePosition(act.pos) && _currentPlayerP->id() == act.id;
}

Action TicTacToe::_nextAction() const {
    if (_currentPlayerP == _player1P) {
        return _player1P->action(_board);
    } else if (_currentPlayerP == _player2P) {
        return _player2P->action(_board);
    } else {
        return Action(BoardEntry::None,BoardPosition(0,0));
    }
}

bool TicTacToe::_isWinner(BoardEntry id) const {
    return _board.isWinner(id);
}

IAgent* TicTacToe::_nextPlayerP(IAgent* currentPlayerP) const {
    if (currentPlayerP == _player1P) {
        return _player2P;
    } else if (currentPlayerP == _player2P) {
        return _player1P;
    }
    return nullptr;
}

void TicTacToe::_setPosition(BoardEntry id, int row, int col) {
    if (id == _player1P->id()) {
        _board.array[row][col] = X;

    } else if (id == _player2P->id()) {
        _board.array[row][col] = O;
    }
}

BoardEntry TicTacToe::_idToBoardEntry(int id) const {
    if (id == _player1P->id()) {
        return X;
    } else if (id == _player2P->id()) {
        return O;
    } else {
        return BoardEntry::None;
    }
}