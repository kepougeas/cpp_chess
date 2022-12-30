#include "../../includes/Equilattechess.hpp"
#include <vector>

Queen::Queen(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_name = PieceName::Queen;
    this->_displayPiece = new sf::Texture();
    if (!this->_displayPiece->loadFromFile(color == WHITE ? WHITE_QUEEN_IMG : BLACK_QUEEN_IMG)) {
        printf("Error loading image for queen\n");
        exit(1);
    }
}

Queen::~Queen()
{}

std::vector<boardPos> Queen::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos checkedPos;
    char posCheckerRet;

    checkedPos = this->_position;
    // A Queen can move diagonally and horizontally in both directions.
    // Checking all diagonals
    while (++checkedPos.x <= 7 && ++checkedPos.y <= 7 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        // Cannot move past more than one ennemy
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while(++checkedPos.x <= 7 && --checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && --checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && ++checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }

    // Checking all straight lines
    checkedPos = this->_position;
    while (++checkedPos.x <= 7 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while(++checkedPos.y <= 7 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.y >= 0 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }

    return possibleMoves;
}

bool Queen::move(boardPos destPos)
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