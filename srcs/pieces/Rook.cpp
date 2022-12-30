#include "../../includes/Equilattechess.hpp"
#include <vector>

Rook::Rook(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_name = PieceName::Rook;
    this->_displayPiece = new sf::Texture();
    if (!this->_displayPiece->loadFromFile(color == WHITE ? WHITE_ROOK_IMG : BLACK_ROOK_IMG)) {
        printf("Error loading image for rook\n");
        exit(1);
    }
}

Rook::~Rook()
{}

std::vector<boardPos> Rook::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos checkedPos;
    char posCheckerRet;

    checkedPos = this->_position;
    // A Rook can move straight in all directions.
    while (++checkedPos.x <= 7 && (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        // Cannot move past one ennemy
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while(++checkedPos.y <= 7 && (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.x >= 0 && (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }
    checkedPos = this->_position;
    while (--checkedPos.y >= 0 && (posCheckerRet = this->_currentGame->isPositionFree(checkedPos, this->_color))) {
        possibleMoves.push_back(checkedPos);
        if (posCheckerRet == 1) {
            break;
        }
    }

    return possibleMoves;
}

bool Rook::move(boardPos destPos)
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