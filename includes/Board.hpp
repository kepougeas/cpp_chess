#pragma once

#include "Equilattechess.hpp"
#include "Game.hpp"
#include "IPiece.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#define CURRENT_PLAYER_TEXT_WHITE "Current player is : WHITE"
#define CURRENT_PLAYER_TEXT_BLACK "Current player is : BLACK"
#define CURR_PLAYER_TEXT_SIZE 15

#define PROMOTION_MENU_TEXT "Click on the desired promotion :"

#define CAPTURED_PIECES_TEXT "Captured pieces :"

class Board
{
public:
    Board(sf::RenderWindow *, Game *, int *);
    ~Board() = default;

    void drawBoard();
    void drawCapturedPieces();
    void drawIndexes();
    void checkClickEvents();
    PieceName promotionMenu(ColorName);
 private:
    sf::RenderWindow   *_window;
    Game               *_currentGame;
    int                *_state;
    sf::Font           _fontGeneral;
    sf::Text           _exitButton;
    sf::Text           _currentPlayerText;
    sf::Text           _capturedPiecesText;
    sf::Text           _indexes[16];
    sf::RectangleShape _chessSquares[8][8];
};