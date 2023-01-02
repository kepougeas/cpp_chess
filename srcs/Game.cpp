#include "../includes/Equilattechess.hpp"
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

Game::Game(int *status)
{
    this->_currentPlayer = WHITE;
    this->_selectedPiece = nullptr;
    this->_status = status;
}

Game::~Game()
{
    this->_gamePieces.clear();
}

// Function returns 0 for non free position (same color or out of bound)
//                  1 for attackable position (enemy color)
//                  2 for free position
positionFreeType Game::isPositionFree(boardPos toCheck, ColorName colorOfChecker)
{
    boardPos currPos;
    IPiece *pieceToDest;

    // Obviously cannot move outside the board
    if (toCheck.x < 0 || toCheck.x > 7 || toCheck.y < 0 || toCheck.y > 7) {
        return NON_FREE;
    }

    // Position is empty
    pieceToDest = this->getPieceOfPos(toCheck);
    if (pieceToDest == nullptr) {
        return IS_FREE;
    }

    // If same color, non free. Attackable position otherwise.
    return pieceToDest->getColor() == colorOfChecker ? NON_FREE : ENEMY_AT_POSITION;
}

IPiece *Game::getPieceOfPos(boardPos toGet)
{
    for(IPiece *piece : this->_gamePieces)
    {
        if (toGet == piece->getPosition()) {
            return piece;
        }
    }

    return nullptr;
}

void Game::removePiece(IPiece *piece)
{
    std::vector<IPiece*>::iterator it;

    it = remove(this->_gamePieces.begin(), this->_gamePieces.end(), piece);
    this->_gamePieces.erase(it);
}

checkMateSituation Game::checkNextKingSituation(IPiece *pieceToMove, boardPos nextPosition)
{
    // We check if the given nextPosition inflicts a check to checkColor's King.
    // This way possibleMove can be removed to prevent player from moving a piece to this location
    IPiece                *king;
    std::vector<IPiece*>  savedBoardState = this->_gamePieces; // Saving the current board
    std::vector<boardPos> possibleEnemyMoves;
    boardPos              savedPiecePosition = pieceToMove->getPosition();
    bool                  savedPieceEnPassant = pieceToMove->getEnPassant();
    
    // Get the king to check and saving rooks during move simulation
    if (pieceToMove->getName() == King) {
        king = pieceToMove;
    }
    else {
        for (IPiece *piece : this->_gamePieces) {
            if (piece->getName() == King && piece->getColor() == pieceToMove->getColor()) {
                king = piece;
                break;
            }
        }
    }

    // Simulate the piece's move
    pieceToMove->move(nextPosition, true);

    // Get the enemy pieces' possibleMoves
    for (IPiece *piece : this->_gamePieces) {
        if (piece->getColor() != pieceToMove->getColor()) {
            possibleEnemyMoves = piece->getPossibleMoves();
            for (boardPos currPos : possibleEnemyMoves) {
                if (currPos == king->getPosition()) {
                    // If enemy has a possible move to the king, we are in check.
                    // Undo our simulated move.
                    this->_gamePieces = savedBoardState;
                    pieceToMove->move(savedPiecePosition, true);
                    pieceToMove->setEnPassant(savedPieceEnPassant);

                    return CHECK;
                }
            }
        }
    }

    // If none of the enemy's pieces can attack king, then it is OK
    this->_gamePieces = savedBoardState;
    pieceToMove->move(savedPiecePosition, true);
    pieceToMove->setEnPassant(savedPieceEnPassant);

    return NORMAL;
}

checkMateSituation Game::checkMateChecker(ColorName checkedColor)
{
    // We check if given checkedColor is in a checkMate situation
    // Basically if any move of the checkedColor player is in CHECK, then we have CHECKMATE
    std::vector<boardPos> possibleMoves;

    for (IPiece *piece : this->_gamePieces) {
        if (piece->getColor() == checkedColor) {
            possibleMoves = piece->getPossibleMoves();
            for (boardPos currPos : possibleMoves) {
                if (this->checkNextKingSituation(piece, currPos) == NORMAL) {
                    return NORMAL;
                }
            }
        }
    }

    return CHECKMATE;
}

void Game::finishGame()
{
    // the current player is the loser

    printf("Player %s WON !\n", this->_currentPlayer == WHITE ? "BLACK" : "WHITE");
    *this->_status = EXIT_STATE;
}

void Game::promotePawn(IPiece *pawn, PieceName promotedTo)
{
    IPiece *promotedPiece;

    switch (promotedTo) {
        case Pawn :
            promotedPiece = new class Pawn(this, pawn->getColor(), pawn->getPosition());
            break;
        case Bishop :
            promotedPiece = new class Bishop(this, pawn->getColor(), pawn->getPosition());
            break;
        case Knight :
            promotedPiece = new class Knight(this, pawn->getColor(), pawn->getPosition());
            break;
        case Rook :
            promotedPiece = new class Rook(this, pawn->getColor(), pawn->getPosition());
            break;
        case Queen :
            promotedPiece = new class Queen(this, pawn->getColor(), pawn->getPosition());
            break;
        case King :
            promotedPiece = pawn; // Cannot become King
            break;
    }

    this->removePiece(pawn);
    this->addPiece(promotedPiece);   
}

// Reset En Passant must be used in the beginning of the current player round
void Game::resetEnPassant()
{
    // We set the En Passant flag to false for Pawns
    for (IPiece *piece : this->_gamePieces) {
        if (piece->getColor() == this->_currentPlayer && piece->getName() == PieceName::Pawn) {
            piece->setEnPassant(false);
        }
    }
}