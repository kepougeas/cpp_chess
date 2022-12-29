#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

class Queen : public IPiece
{
public:
    Queen (Game*, ColorName, boardPos);
    virtual ~Queen();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual bool move(boardPos);
protected:
    Game     *_currentGame;
};