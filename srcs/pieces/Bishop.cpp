#include "../../includes/Equilattechess.hpp"
#include <vector>

Bishop::Bishop(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
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
    char posCheckerRet;

    checkedPos = this->_position;
    // A Bishop can move diagonally in both directions.
    // Checking all diagonals
    while (++checkedPos.x <= 7 && ++checkedPos.y <= 7 &&
            (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color)))
    {
        possibleMoves.push_back(checkedPos);
        // We cannot get past more than one enemy
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

    return possibleMoves;
}

// Returns the captured piece if any, nullptre otherwise
IPiece *Bishop::move(boardPos destPos, bool simulated)
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