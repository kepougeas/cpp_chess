#include "../../includes/Equilattechess.hpp"
#include <vector>

King::King(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_name = PieceName::King;
    this->_displayPiece = new sf::Texture();
    if (!this->_displayPiece->loadFromFile(color == WHITE ? WHITE_KING_IMG : BLACK_KING_IMG)) {
        printf("Error loading image for king\n");
        exit(1);
    }
}

King::~King()
{}

std::vector<boardPos> King::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos checkedPos;

    // A King can only move one step in every direction.
    checkedPos = this->_position;
    checkedPos.x++;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x--;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.y++;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.y--;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x++;
    checkedPos.y++;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x--;
    checkedPos.y++;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x++;
    checkedPos.y--;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }
    checkedPos = this->_position;
    checkedPos.x--;
    checkedPos.y--;
    if (this->_currentGame->isPositionFree(checkedPos, this->_color)) {
        possibleMoves.push_back(checkedPos);
    }

    return possibleMoves;
}

IPiece *King::move(boardPos destPos)
{
    IPiece *destPiece = this->_currentGame->getPieceOfPos(destPos);

    // Piece is attacking opponent
    if (destPiece && destPiece->getColor() != this->_color) {
        this->_currentGame->removePiece(destPiece);
    }

    this->_position = destPos;

    return destPiece;
}