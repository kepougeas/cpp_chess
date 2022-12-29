#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

class Pawn : public IPiece
{
public:
    Pawn (Game*, ColorName, boardPos);
    virtual ~Pawn();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual bool move(boardPos);
protected:
    Game     *_currentGame;
    boardPos _initialPosition;
};