#pragma once

#include "IPiece.hpp"

// TODO: checkMateChecker
// TODO: possibleMoves behavior in case of king trouble

// TODO: en passant
// TODO: promote
// TODO: castling

// TODO: capture history for each player
// TODO: side display of chess compliant indexes

// CHESS BOARD OVERVIEW
//
//     0   1   2   3   4   5   6   7
//   |---------------------------------> Yaxis
// 0 8 R | Kn| B | Q | K | B | Kn| R |
//   |--------------------------------     BLACK
// 1 7 P | P | P | P | P | P | P | P |            P = Pawn
//   |--------------------------------            R = Rook
// 2 6   |   |   |   |   |   |   |   |            Kn = Knight
//   |--------------------------------            B = Bishop
// 3 5   |   |   |   |   |   |   |   |            Q = Queen
//   |--------------------------------            K = King
// 4 4   |   |   |   |   |   |   |   |
//   |--------------------------------
// 5 3   |   |   |   |   |   |   |   |
//   |--------------------------------
// 6 2 P | P | P | P | P | P | P | P |
//   |--------------------------------     WHITE
// 7 1 R | Kn| B | Q | K | B | Kn| R |
//   |-A---B---C---D---E---F---G---H--
//   |
//   v
// Xaxis

class Game
{
public:
    Game();
    ~Game();
    void addPiece(IPiece *piece) { this->_gamePieces.push_back(piece); };
    void removePiece(IPiece *piece);
    void printAllPieces() { for(IPiece *piece : this->_gamePieces) {piece->printPosition();} };
    char isPositionFree(boardPos, ColorName);
    IPiece *getPieceOfPos(boardPos);
    IPiece *getSelectedPiece() { return this->_selectedPiece; };
    void setSelectedPiece(IPiece *piece) { this->_selectedPiece = piece; };
    ColorName getCurrentPlayer() { return this->_currentPlayer; };
    void finishTurn() { this->_currentPlayer = this->_currentPlayer == WHITE ? BLACK : WHITE; };
private:
    std::vector<IPiece *> _gamePieces;
    ColorName             _currentPlayer;
    IPiece                *_selectedPiece;
};