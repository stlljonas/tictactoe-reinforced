#include "TicTacToe.h"
#include <algorithm>

std::string Board::string() const {
    
    // e.g.
    // +---+---+---+
    // | X | O |   |
    // +---+---+---+
    // |   | X |   |
    // +---+---+---+
    // | O |   | X |
    // +---+---+---+

    std::string boardString = "+---+---+---+";
    for (int row = 0; row < 3; ++row) {
        boardString += "\n|";
        for (int col = 0; col < 3; ++col) {
            boardString += " ";
            boardString += boardEntryToString(array[row][col]);
            boardString += " ";
            boardString += "|";
        }
        boardString += "\n+---+---+---+";
    }
    return boardString;
}

std::string Board::boardEntryToString(BoardEntry entry) const {
        switch(entry) {
            case(BoardEntry::None):
                return " ";
            case(X):
                return "X";
            case(O):
                return "O";
            default:
                return " ";
        }
    }


std::list<BoardPosition> Board::freePositions() const {
    std::list<BoardPosition> posList = {};
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (array[row][col] == 0) {
                posList.push_back(BoardPosition(row,col));
            }
        }
    }
    return posList;
}

bool Board::isFreePosition(BoardPosition pos) const {
    const std::list<BoardPosition> posList = freePositions();
    return (std::find(posList.begin(),posList.end(), pos) != posList.end());
}

void Board::reset() {
    array = {};
}

std::string TicTacToe::string() const {
    return _board.string();
}

const GameState TicTacToe::gameState() const {
    return _gameState;
}

const Board TicTacToe::board() const {
    return _board;
}

float TicTacToe::reward(const IAgent& player) const {
    if (_isWinner(player.id())) {
        return 1.0;
    } else if (_isWinner(_nextPlayerId(player.id()))) {
        return -1.0;
    } else {
        return 0.0;
    }
}

std::list<Action> TicTacToe::possibleActions(const IAgent& agent) const {
    std::list<BoardPosition> posList = _board.freePositions();
    std::list<Action> actionList;
    const int id = agent.id();
    for (auto it = posList.begin(); it != posList.end(); ++it) {
        actionList.push_back(Action(id, *it));
    }
    return actionList;
}

int TicTacToe::currentPlayerId() const {
    return _currentPlayerId;
}

void TicTacToe::start() {
    _board.reset();
    _moveNumber = 0;
    _currentPlayerId = _player1.id();
}

void TicTacToe::start(const IAgent& startingPlayer) {
    _board.reset();
    _moveNumber = 0;
    _currentPlayerId = startingPlayer.id();
    _gameState = GameState::TURN_PLAYER;
}

void TicTacToe::reset() {
    _gameState = GameState::START;
}

void TicTacToe::round(Action act) {
    if (not _isValidAction(act)) {
        return; // repeat
    } else {
        _board.array[act.pos.row][act.pos.col] = _idToBoardEntry(act.id);
        if (_isWinner(_player1.id())) {
            _gameState = GameState::WIN_PLAYER_1;
        } else if (_isWinner(_player2.id())) {
            _gameState = GameState::WIN_PLAYER_2;
        } else if (_board.freePositions().size() == 0) {
            _gameState = GameState::TIE;
        } else {
            _currentPlayerId = _nextPlayerId(_currentPlayerId);
        }
    }
}

void TicTacToe::exit() {
    _gameState = GameState::EXIT;
}

bool TicTacToe::_isValidAction(Action act) const {
    return _board.isFreePosition(act.pos) && _currentPlayerId == act.id;
}

bool TicTacToe::_isWinner(const int id) const {
    // check horizontal
    for(int i = 0; i < 3; ++i) {
        if (_board.array[0][i] == _board.array[1][i]
            == _board.array[2][i] == id) {
            return true;
        }
    }
    // check vertical
    for (int i = 0; i < 3; ++i) {
        if (_board.array[i][0] == _board.array[i][1]
            == _board.array[i][2] == id) {
            return true;
        }
    }
    // check diagonal
    if (_board.array[0][0] == _board.array[1][1]
        == _board.array[2][2] == id) {
        return true;
    }
    if (_board.array[2][0] == _board.array[1][1]
        == _board.array[0][2] == id) {
        return true;
    }
    return false;
}


int TicTacToe::_nextPlayerId(int currentPlayerId) const {
    if (currentPlayerId == _player1.id()) {
        return _player2.id();
    } else if (currentPlayerId == _player2.id()) {
        return _player1.id();
    }
    return 0;
}

void TicTacToe::_setPosition(int id, int row, int col) {
    if (id == _player1.id()) {
        _board.array[row][col] = X;

    } else if (id == _player2.id()) {
        _board.array[row][col] = O;
    }
}

BoardEntry TicTacToe::_idToBoardEntry(int id) const {
    if (id == _player1.id()) {
        return X;
    } else if (id == _player2.id()) {
        return O;
    } else {
        return BoardEntry::None;
    }
}