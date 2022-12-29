#include "../../includes/Equilattechess.hpp"
#include <vector>

Knight::Knight(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_name = PieceName::Knight;
}

Knight::~Knight()
{}

std::vector<boardPos> Knight::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos checkedPos = this->_position;

    // Knights can jump over pieces and do an L shaped move
    // Basically 8 moves to check
    checkedPos.x += 1;
    checkedPos.y -= 2;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x -= 1;
    checkedPos.y -= 2;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }

    checkedPos = this->_position;
    checkedPos.x -= 2;
    checkedPos.y -= 1;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x -= 2;
    checkedPos.y += 1;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }

    checkedPos = this->_position;
    checkedPos.x -= 1;
    checkedPos.y += 2;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x += 1;
    checkedPos.y += 2;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }

    checkedPos = this->_position;
    checkedPos.x += 2;
    checkedPos.y -= 1;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x += 2;
    checkedPos.y += 1;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }

    return possibleMoves;
}

bool Knight::move(boardPos destPos)
{
    IPiece *destPiece = this->_currentGame->getPieceOfPos(destPos);

    // Piece is attacking opponent
    if (destPiece && destPiece->getColor() != this->_color) {
        printf("Piece %s attacked %s on [X = %i ; Y = %i]\n", enumPieceName[this->_name], enumPieceName[destPiece->getName()], destPos.x, destPos.y);
        this->_currentGame->removePiece(destPiece);
    }

    this->_position = destPos;

    return true;
}