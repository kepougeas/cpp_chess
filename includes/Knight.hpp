#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

#define BLACK_KNIGHT_IMG "assets/black_knight.png"
#define WHITE_KNIGHT_IMG "assets/white_knight.png"

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