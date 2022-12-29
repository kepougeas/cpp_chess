#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

class Knight : public IPiece
{
public:
    Knight (Game*, ColorName, boardPos);
    virtual ~Knight();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual bool move(boardPos);
protected:
    Game     *_currentGame;
};