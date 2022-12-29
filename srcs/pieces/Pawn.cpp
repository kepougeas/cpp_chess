#include "../../includes/Equilattechess.hpp"
#include <vector>

Pawn::Pawn(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
    this->_name = PieceName::Pawn;
}

Pawn::~Pawn()
{}

std::vector<boardPos> Pawn::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos defaultMove;

    // A pawn can only move forward, except on its first move.

    // Default move
    if (this->_color == BLACK) {
            defaultMove = {
                .x = this->_position.x,
                .y = this->_position.y + 1
            };
    }
    else {
        // if White we decrease the index
        defaultMove = {
            .x = this->_position.x,
            .y = this->_position.y - 1
        };
    }

    if (this->_currentGame->isPositionFree(defaultMove, this->_color)) {
        possibleMoves.push_back(defaultMove);
    }
    else {
        return possibleMoves;
    }

    // Check if pawn is on first move
    if (this->_position == this->_initialPosition) {
        boardPos pos;

        if (this->_color == BLACK) {
            // if Black we increase the index on the board
            pos = {
                .x = this->_position.x,
                .y = this->_position.y + 2
            };
        }
        else {
            // if White we decrease the index
            pos = {
                .x = this->_position.x,
                .y = this->_position.y - 2
            };
        }

        if (this->_currentGame->isPositionFree(pos, this->_color)) {
                possibleMoves.push_back(pos);
            }
    }

    return possibleMoves;
}

bool Pawn::move(boardPos destPos)
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