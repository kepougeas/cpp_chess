#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

#define BLACK_BISHOP_IMG "assets/black_bishop.png"
#define WHITE_BISHOP_IMG "assets/white_bishop.png"

class Bishop : public IPiece
{
public:
    Bishop (Game*, ColorName, boardPos);
    virtual ~Bishop();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual IPiece *move(boardPos, bool);
protected:
    Game     *_currentGame;
};