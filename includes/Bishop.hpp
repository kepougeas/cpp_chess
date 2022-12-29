#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

class Bishop : public IPiece
{
public:
    Bishop (Game*, ColorName, boardPos);
    virtual ~Bishop();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual bool move(boardPos);
protected:
    Game     *_currentGame;
};