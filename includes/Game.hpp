#pragma once

#include "IPiece.hpp"


// CHESS BOARD OVERVIEW
//
//     0   1   2   3   4   5   6   7
//   |---------------------------------> Xaxis
// 0 8   |   |   |   |   |   |   |   |
//   |--------------------------------     BLACK
// 1 7   |   |   |   |   |   |   |   |            P = Pawn
//   |--------------------------------            R = Rook
// 2 6 bP|   |wB | wQ|   |   |   |   |            Kn = Knight
//   |--------------------------------            B = Bishop
// 3 5   |   |   |bKn|   |   |   |   |            Q = Queen
//   |--------------------------------            K = King
// 4 4   |   |   |wR |wP |   |   |   |
//   |--------------------------------
// 5 3   |   |   |   |   |   |   |   |
//   |--------------------------------
// 6 2   |   |   |   |   |   |   |   |
//   |--------------------------------     WHITE
// 7 1   |   |   |   |   |   |   |   |
//   |-A---B---C---D---E---F---G---H--
//   |
//   v
// Yaxis





// CHESS BOARD OVERVIEW
//
//     0   1   2   3   4   5   6   7
//   |---------------------------------> Xaxis
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
// Yaxis

class Game
{
public:
    Game();
    ~Game() = default;
    void addPiece(IPiece *piece) { this->_gamePieces.push_back(piece); };
    void removePiece(IPiece *piece);
    void printAllPieces() { for(IPiece *piece : this->_gamePieces) {piece->printPosition();} };
    bool isPositionFree(boardPos, ColorName);
    IPiece *getPieceOfPos(boardPos);
private:
    std::vector<IPiece *> _gamePieces;
};