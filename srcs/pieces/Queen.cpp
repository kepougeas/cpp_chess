#include "../../includes/Equilattechess.hpp"
#include <vector>

Queen::Queen(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
    this->_name = PieceName::Queen;
    this->_displayPiece = new sf::Texture();
    this->_displayPiece->setSmooth(true);
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
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while(++checkedPos.x <= 7 && --checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && --checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && ++checkedPos.y >= 0 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }

    // Checking all straight lines
    checkedPos = this->_position;
    while (++checkedPos.x <= 7 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while(++checkedPos.y <= 7 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.y >= 0 && 
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == ENEMY_AT_POSITION) {
            break;
        }
    }

    return possibleMoves;
}

IPiece *Queen::move(boardPos destPos, bool simulated)
{
    IPiece *destPiece = this->_currentGame->getPieceOfPos(destPos);

    // Piece is attacking opponent
    if (destPiece && destPiece->getColor() != this->_color) {
        if (!simulated) {
            this->_currentGame->addCapturedPiece(destPiece);
        }
        this->_currentGame->removePiece(destPiece);
    }

    this->_position = destPos;
    this->_isFirstMove = simulated ? this->_isFirstMove : false;

    return destPiece;
}