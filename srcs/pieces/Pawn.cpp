#include "../../includes/Equilattechess.hpp"
#include <vector>

Pawn::Pawn(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
    this->_name = PieceName::Pawn;
    this->_enPassant = false;
    this->_displayPiece = new sf::Texture();
    this->_displayPiece->setSmooth(true);
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
    IPiece *enPassantPawn;
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
    if (this->_currentGame->isPositionFree(defaultMove, this->_color) == IS_FREE) {
        possibleMoves.push_back(defaultMove);
    }

    // Check if pawn is on first move
    if (this->_position == this->_initialPosition && !possibleMoves.empty()) {
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
        if (this->_currentGame->isPositionFree(pos, this->_color) == IS_FREE) {
                possibleMoves.push_back(pos);
            }
    }

    // Checking attacks now, Pawns can only attack diagonally
    if (this->_color == BLACK) {
        defaultMove = {
            .x = this->_position.x + 1,
            .y = this->_position.y + 1
        };
        enPassantPawn = this->_currentGame->getPieceOfPos({
            .x = this->_position.x,
            .y = this->_position.y + 1
        });

        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == ENEMY_AT_POSITION) {
            possibleMoves.push_back(defaultMove);
        }
        // Checking En Passant possible attacks
        else if (enPassantPawn && enPassantPawn->getName() == PieceName::Pawn && enPassantPawn->getEnPassant() == true) {
            possibleMoves.push_back(defaultMove);
        }

        defaultMove = {
            .x = this->_position.x + 1,
            .y = this->_position.y - 1
        };
        enPassantPawn = this->_currentGame->getPieceOfPos({
            .x = this->_position.x,
            .y = this->_position.y - 1
        });

        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == ENEMY_AT_POSITION) {
            possibleMoves.push_back(defaultMove);
        }
        // Checking En Passant possible attacks
        else if (enPassantPawn && enPassantPawn->getName() == PieceName::Pawn && enPassantPawn->getEnPassant() == true) {
            possibleMoves.push_back(defaultMove);
        }
    }
    else {
         defaultMove = {
            .x = this->_position.x - 1,
            .y = this->_position.y - 1
        };
        enPassantPawn = this->_currentGame->getPieceOfPos({
            .x = this->_position.x,
            .y = this->_position.y - 1
        });
        
        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == ENEMY_AT_POSITION) {
            possibleMoves.push_back(defaultMove);
        }
        // Checking En Passant possible attacks
        else if (enPassantPawn && enPassantPawn->getName() == PieceName::Pawn && enPassantPawn->getEnPassant() == true) {
            possibleMoves.push_back(defaultMove);
        }

        defaultMove = {
            .x = this->_position.x - 1,
            .y = this->_position.y + 1
        };
        enPassantPawn = this->_currentGame->getPieceOfPos({
            .x = this->_position.x,
            .y = this->_position.y + 1
        });

        if (this->_currentGame->isPositionFree(defaultMove, this->_color) == ENEMY_AT_POSITION) {
            possibleMoves.push_back(defaultMove);
        }
        // Checking En Passant possible attacks
        else if (enPassantPawn && enPassantPawn->getName() == PieceName::Pawn && enPassantPawn->getEnPassant() == true) {
            possibleMoves.push_back(defaultMove);
        }
    }

    return possibleMoves;
}

IPiece *Pawn::move(boardPos destPos, bool simulated)
{
    IPiece *destPiece = this->_currentGame->getPieceOfPos(destPos);

    // en passant flag for first double move
    if (destPos.x == this->_position.x + 2 || destPos.x == this->_position.x - 2) {
        this->_enPassant = true;
    }
    // Piece is attacking opponent
    if (destPiece && destPiece->getColor() != this->_color) {
        if (!simulated) {
            this->_currentGame->addCapturedPiece(destPiece);
        }
        this->_currentGame->removePiece(destPiece);
    }

    // We check if we are doing en passant attack
    if (destPiece == nullptr && destPos.y != this->_position.y) {
        if (destPos.y == this->_position.y + 1) {
            destPiece = this->_currentGame->getPieceOfPos({.x = this->_position.x, .y = this->_position.y + 1});
        }
        else if (destPos.y == this->_position.y - 1) {
            destPiece = this->_currentGame->getPieceOfPos({.x = this->_position.x, .y = this->_position.y - 1});
        }
        if (destPiece && destPiece->getName() == PieceName::Pawn && destPiece->getEnPassant() == true) {
            // En Passant capture !
            if (!simulated) {
                this->_currentGame->addCapturedPiece(destPiece);
            }
            this->_currentGame->removePiece(destPiece);
        }
    }

    this->_position = destPos;
    this->_isFirstMove = simulated ? this->_isFirstMove : false;

    return destPiece;
}