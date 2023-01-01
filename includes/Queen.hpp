#pragma once

#include "Equilattechess.hpp"
#include "IPiece.hpp"

#define BLACK_QUEEN_IMG "assets/black_queen.png"
#define WHITE_QUEEN_IMG "assets/white_queen.png"

class Queen : public IPiece
{
public:
    Queen (Game*, ColorName, boardPos);
    virtual ~Queen();
    virtual std::vector<boardPos> getPossibleMoves();
    virtual IPiece *move(boardPos);
protected:
    Game     *_currentGame;
};