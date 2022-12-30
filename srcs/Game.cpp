#include "../includes/Equilattechess.hpp"
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

Game::Game()
{
    this->_currentPlayer = WHITE;
    this->_selectedPiece = nullptr;
}

Game::~Game()
{
    this->_gamePieces.clear();
}

// Function returns 0 for non free position (same color or out of bound)
//                  1 for attackable position (enemy color)
//                  2 for free position
char Game::isPositionFree(boardPos toCheck, ColorName colorOfChecker)
{
    boardPos currPos;
    IPiece *pieceToDest;

    // Obviously cannot move outside the board
    if (toCheck.x < 0 || toCheck.x > 7 || toCheck.y < 0 || toCheck.y > 7) {
        return 0;
    }

    // Position is empty
    pieceToDest = this->getPieceOfPos(toCheck);
    if (pieceToDest == nullptr) {
        return 2;
    }

    // If same color, non free. Attackable position otherwise.
    return pieceToDest->getColor() == colorOfChecker ? 0 : 1;
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

    printf("Removed %s from the game\n", enumPieceName[piece->getName()]);
    it = remove(this->_gamePieces.begin(), this->_gamePieces.end(), piece);
    this->_gamePieces.erase(it);
}