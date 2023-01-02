#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

#define BLACK_ROOK_IMG "assets/black_rook.png"
#define WHITE_ROOK_IMG "assets/white_rook.png"

class Rook : public IPiece
{
public:
    Rook (Game*, ColorName, boardPos);
    virtual ~Rook();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual IPiece *move(boardPos, bool);
protected:
    Game     *_currentGame;
};