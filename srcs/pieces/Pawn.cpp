#include "../../includes/Equilattechess.hpp"
#include <vector>

Pawn::Pawn(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
    this->_name = PieceName::Pawn;
    this->_displayPiece = new sf::Texture();
    if (!this->_displayPiece->loadFromFile(color == WHITE ? WHITE_PAWN_IMG : BLACK_PAWN_IMG)) {
        printf("Error loading image for pawn\n");
        exit(1);
    }
}

Pawn::~Pawn()
{}

std::vector<boardPos> Pawn::getPossibleMoves()
{
    std::vector<boardPos> possibleMoves;
    boardPos defaultMove;
    char posCheckerRet;

    // A pawn can only move forward, except on its first move.

    // Default move
    if (this->_color == BLACK) {
            defaultMove = {
                .x = this->_position.x + 1,
                .y = this->_position.y
            };
    }
    else {
        // if White we decrease the index
        defaultMove = {
            .x = this->_position.x - 1,
            .y = this->_position.y
        };
    }

    // Can only move this way if the position is absolutely empty.
    if (this->_currentGame->isPositionFree(defaultMove, this->_color) == 2) {
        possibleMoves.push_back(defaultMove);
    }

    // Check if pawn is on first move
    if (this->_position == this->_initialPosition) {
        boardPos pos;

        if (this->_color == BLACK) {
            // if Black we increase the index on the board
            pos = {
                .x = this->_position.x + 2,
                .y = this->_position.y
            };
        }
        else {
            // if White we decrease the index
            pos = {
                .x = this->_position.x - 2,
                .y = this->_position.y
            };
        }

        // Same, can only move forward if position is empty
        if (this->_currentGame->isPositionFree(pos, this->_color) == 2) {
                possibleMoves.push_back(pos);
            }
    }

    // Checking attacks now, Pawns can only attack diagonally
    if (this->_color == BLACK) {
        defaultMove = {
            .x = this->_position.x + 1,
            .y = this->_position.y + 1
        };
        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == 1) {
            possibleMoves.push_back(defaultMove);
        }
        defaultMove = {
            .x = this->_position.x + 1,
            .y = this->_position.y - 1
        };
        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == 1) {
            possibleMoves.push_back(defaultMove);
        }
    }
    else {
         defaultMove = {
            .x = this->_position.x - 1,
            .y = this->_position.y - 1
        };
        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == 1) {
            possibleMoves.push_back(defaultMove);
        }
        defaultMove = {
            .x = this->_position.x - 1,
            .y = this->_position.y + 1
        };
        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == 1) {
            possibleMoves.push_back(defaultMove);
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