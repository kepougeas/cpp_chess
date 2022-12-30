#include "../../includes/Equilattechess.hpp"
#include <vector>

Bishop::Bishop(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_name = PieceName::Bishop;
    this->_displayPiece = new sf::Texture();
    if (!this->_displayPiece->loadFromFile(color == WHITE ? WHITE_BISHOP_IMG : BLACK_BISHOP_IMG)) {
        printf("Error load image for bishop\n");
        exit(1);
    }
}

Bishop::~Bishop()
{}

std::vector<boardPos> Bishop::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos checkedPos;

    checkedPos = this->_position;
    // A Bishop can move diagonally in both directions.
    // Checking all diagonals
    while (++checkedPos.x <= 7 && ++checkedPos.y <= 7 &&
            this->_currentGame->isPositionFree(checkedPos, this->_color))
    {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    while(++checkedPos.x <= 7 && --checkedPos.y >= 0 &&
            this->_currentGame->isPositionFree(checkedPos, this->_color))
    {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && --checkedPos.y >= 0 &&
            this->_currentGame->isPositionFree(checkedPos, this->_color))
    {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && ++checkedPos.y >= 0 &&
            this->_currentGame->isPositionFree(checkedPos, this->_color))
    {
        possibleMoves.push_back(checkedPos);
    }

    return possibleMoves;
}

bool Bishop::move(boardPos destPos)
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