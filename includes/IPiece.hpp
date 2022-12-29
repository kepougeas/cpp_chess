#pragma once

#include <string>
#include <vector>

struct boardPos {
    int x;
    int y;
};

enum PieceName {
    Pawn,
    Bishop,
    Knight,
    Rook,
    Queen,
    King
};

static const char *enumPieceName[] = {
    "Pawn",
    "Bishop",
    "Knight",
    "Rook",
    "Queen",
    "King"
};

enum ColorName {
    WHITE,
    BLACK
};

class   IPiece
{
public:
    virtual ~IPiece() = default;

    virtual std::vector<boardPos> getPossibleMoves() = 0;
    virtual bool move(boardPos) = 0;

    boardPos getPosition() { return this->_position; };
    PieceName getName() { return this->_name; };
    ColorName getColor() { return this->_color; };
    void printPossibleMoves();
    void printPosition() { printf("Piece %s is at [X = %i ; Y = %i]\n", enumPieceName[this->_name], this->_position.x, this->_position.y); };
protected:
    PieceName        _name;
    boardPos         _position;
    ColorName        _color;
};

inline bool operator==(const boardPos &pos1, const boardPos &pos2)
{
    return pos1.x == pos2.x && pos1.y == pos2.y;
}

inline void IPiece::printPossibleMoves()
{
    std::vector<boardPos> possibleMoves;

    possibleMoves = this->getPossibleMoves();
    printf("Piece %s can move to the following positions : \n", enumPieceName[this->_name]);

    for (boardPos pos : possibleMoves) {
        printf("[X = %i ; Y = %i]\n", pos.x, pos.y);
    }
}