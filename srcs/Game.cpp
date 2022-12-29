#include "../includes/Equilattechess.hpp"
#include <iterator>
#include <type_traits>
#include <vector>

Game::Game()
{
}

bool Game::isPositionFree(boardPos toCheck, ColorName colorOfChecker)
{
    boardPos currPos;

    // Obviously cannot move outside the board
    if (toCheck.x < 0 || toCheck.x > 7 || toCheck.y < 0 || toCheck.y > 7) {
        return false;
    }

    for(IPiece *piece : this->_gamePieces)
    {
        currPos = piece->getPosition();
        if (currPos == toCheck && this->getPieceOfPos(currPos)->getColor() == colorOfChecker) {
            return false;
        }
    }

    return true;
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