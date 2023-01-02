#include "../../includes/Equilattechess.hpp"
#include <vector>

King::King(Game *currentGame, ColorName color, boardPos position)
{
    this->_currentGame = currentGame;
    this->_color = color;
    this->_position = position;
    this->_initialPosition = position;
    this->_name = PieceName::King;
    this->_displayPiece = new sf::Texture();
    this->_displayPiece->setSmooth(true);
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
    IPiece *rook;
    char xAxisIndex;

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

    // Castling check
    // Castling can occur if Rook and King are on their first move
    // There are no pawns between them
    // King will not pass through Check
    if (this->_isFirstMove) {
        // Set the proper index depending on player
        xAxisIndex = this->_color == WHITE ? 7 : 0;
        // King side castling check
        rook = this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 7});
        // If first move and no pawns in between and King does not go through CHECK
        if (rook && rook->isFirstMove() 
        && this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 6}) == nullptr 
        && this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 5}) == nullptr
        && this->_currentGame->checkNextKingSituation(this, {.x = xAxisIndex, .y = 6}) == NORMAL
        && this->_currentGame->checkNextKingSituation(this, {.x = xAxisIndex, .y = 5}) == NORMAL) {
            possibleMoves.push_back({.x = xAxisIndex, .y = 6});
        }
        // Queen side castling check
        rook = this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 0});
        // If first move and no pawns in between and King does not go through CHECK
        if (rook && rook->isFirstMove() 
        && this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 1}) == nullptr 
        && this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 2}) == nullptr
        && this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 3}) == nullptr
        && this->_currentGame->checkNextKingSituation(this, {.x = xAxisIndex, .y = 1}) == NORMAL
        && this->_currentGame->checkNextKingSituation(this, {.x = xAxisIndex, .y = 2}) == NORMAL
        && this->_currentGame->checkNextKingSituation(this, {.x = xAxisIndex, .y = 3}) == NORMAL) {
            possibleMoves.push_back({.x = xAxisIndex, .y = 2});
        }
    }

    return possibleMoves;
}

IPiece *King::move(boardPos destPos, bool simulated)
{
    IPiece *destPiece = this->_currentGame->getPieceOfPos(destPos);
    char xAxisIndex;

    // Piece is attacking opponent
    if (destPiece && destPiece->getColor() != this->_color) {
        if (!simulated) {
            this->_currentGame->addCapturedPiece(destPiece);
        }
        this->_currentGame->removePiece(destPiece);
    }

    // Piece is castling
    // King Side
    if (this->_position.y + 1 < destPos.y && !simulated) {
        xAxisIndex = this->_color == WHITE ? 7 : 0;
        destPiece = this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 7});
        destPiece->move({.x = xAxisIndex, .y = 5}, false);
    }
    // Queen Side
    else if (this->_position.y - 1 > destPos.y && !simulated) {
        xAxisIndex = this->_color == WHITE ? 7 : 0;
        destPiece = this->_currentGame->getPieceOfPos({.x = xAxisIndex, .y = 0});
        destPiece->move({.x = xAxisIndex, .y = 3}, false);
    }

    this->_position = destPos;
    this->_isFirstMove = simulated ? this->_isFirstMove : false;

    return destPiece;
}