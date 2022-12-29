#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

class Rook : public IPiece
{
public:
    Rook (Game*, ColorName, boardPos);
    virtual ~Rook();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual bool move(boardPos);
protected:
    Game     *_currentGame;
};