#include "../includes/Equilattechess.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>

Board::Board(sf::RenderWindow *window, Game *currentGame, int *state)
{
    this->_window = window;
    this->_state = state;
    this->_currentGame = currentGame;

    // Loading the fonts
    if (!this->_fontGeneral.loadFromFile(TITLE_FONT_PATH)) {
        printf("Could not load font");
        exit(-1);
    }

    // Creating the exit button
    this->_exitButton.setFont(this->_fontGeneral);
    this->_exitButton.setString(EXIT_TEXT);
    this->_exitButton.setCharacterSize(MENU_TEXT_SIZE);
    this->_exitButton.setFillColor(sf::Color::White);
    this->_exitButton.setPosition(this->_window->getSize().x - this->_exitButton.getGlobalBounds().width * 2, 0);

    // current player turn display
    this->_currentPlayerText.setFont(this->_fontGeneral);
    this->_currentPlayerText.setCharacterSize(CURR_PLAYER_TEXT_SIZE);
    this->_currentPlayerText.setFillColor(sf::Color::Red);
    this->_currentPlayerText.setPosition(this->_window->getSize().x - 400, 150);

    // Creating the ChessBoard squares
    bool colorToggle = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape square(sf::Vector2f(120, 120));
            square.setFillColor(colorToggle == true ? sf::Color::White : sf::Color::Black);
            square.setPosition(j * 120, i * 120);
            this->_chessSquares[i][j] = square;
            colorToggle = !colorToggle;
        }
        colorToggle = !colorToggle;
    }
};

void Board::drawBoard()
{
    IPiece *piece;

    // We draw EXIT button player turn display, the main board and all the pieces
    this->_window->draw(this->_exitButton);
    this->_currentPlayerText.setString(this->_currentGame->getCurrentPlayer() == WHITE ? CURRENT_PLAYER_TEXT_WHITE : CURRENT_PLAYER_TEXT_BLACK);
    this->_window->draw(this->_currentPlayerText);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            piece = this->_currentGame->getPieceOfPos({.x = i, .y = j});
            this->_window->draw(this->_chessSquares[i][j]);
            if (piece != nullptr) {
                sf::Sprite sprite;
                sprite.setTexture(*piece->getTexture());
                sprite.setPosition(j * 120 + 20, i * 120 + 20);
                this->_window->draw(sprite);
            }
        }
    }

    // If there is a selected Piece we draw square around it and possible moves on board
    if ((piece = this->_currentGame->getSelectedPiece()) != nullptr) {
        sf::RectangleShape selectSquare(sf::Vector2f(100, 100));
        boardPos piecePos = piece->getPosition();
        std::vector<boardPos> possibleMoves = piece->getPossibleMoves();

        selectSquare.setFillColor(sf::Color(255,255,255,0));
        selectSquare.setOutlineColor(sf::Color::Green);
        selectSquare.setOutlineThickness(10);
        selectSquare.setPosition(piecePos.y * 120 + 10, piecePos.x * 120 + 10);
        this->_window->draw(selectSquare);

        for (boardPos currPos: possibleMoves)
        {
            sf::RectangleShape possibleMoveSquare(sf::Vector2f(100, 100));
            
            possibleMoveSquare.setFillColor(sf::Color(255, 255, 255, 0));
            possibleMoveSquare.setOutlineColor(sf::Color::Blue);
            possibleMoveSquare.setOutlineThickness(10);
            possibleMoveSquare.setPosition(currPos.y * 120 + 10, currPos.x * 120 + 10);
            this->_window->draw(possibleMoveSquare);
        }
    }

    this->checkClickEvents();
}

void Board::checkClickEvents()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // Quick sleep to prevent annoying multiple clicking
        usleep(100000);

        sf::Vector2i clicPosition = sf::Mouse::getPosition(*this->_window);
        sf::Vector2f exitButtonPosition = this->_exitButton.getPosition();
        sf::FloatRect exitButtonSize = this->_exitButton.getGlobalBounds();
        sf::Vector2f checkedPiecePos;
        sf::FloatRect checkedPosSize;
        IPiece *clickedPiece;

        // We clicked EXIT
        if ((clicPosition.x >= exitButtonPosition.x && clicPosition.x <= (exitButtonPosition.x + exitButtonSize.width * 2))
        && (clicPosition.y >= exitButtonPosition.y && clicPosition.y <= (exitButtonPosition.y + exitButtonSize.height * 2)))
        {
            *this->_state = EXIT_STATE;
        }

        // If there is no selected piece
        if ((clickedPiece = this->_currentGame->getSelectedPiece()) == nullptr) {
        //Check for a piece click
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    checkedPiecePos = this->_chessSquares[i][j].getPosition();
                    checkedPosSize = this->_chessSquares[i][j].getGlobalBounds();
                    if ((clicPosition.x > checkedPiecePos.x && clicPosition.x < (checkedPiecePos.x + checkedPosSize.width))
                    && (clicPosition.y > checkedPiecePos.y && clicPosition.y < (checkedPiecePos.y + checkedPosSize.height)))
                    {
                        // We clicked on a piece
                        clickedPiece = this->_currentGame->getPieceOfPos({.x = i, .y = j});
                        // If this is the right player then we can select
                        if (clickedPiece == nullptr ||
                        this->_currentGame->getCurrentPlayer() == clickedPiece->getColor()) {
                            this->_currentGame->setSelectedPiece(clickedPiece);
                        }
                    }
                }
            }
        }
        // Check for click on possible moves (unselect piece if outside of possible moves)
        else {
            std::vector<boardPos> possibleMoves = clickedPiece->getPossibleMoves();

            // We check if clic happened in any of the possible moves area
            for (boardPos currPos : possibleMoves) {
                // Tricky reversed indexes (sub optimal for understanding but I have time constraint)
                if ((clicPosition.x > (currPos.y * 120) && clicPosition.x < (currPos.y * 120 + 120))
                && (clicPosition.y > (currPos.x * 120) && clicPosition.y < (currPos.x * 120 + 120)))
                {
                    // Clic happened on a possible move, so we move the piece
                    clickedPiece->move(currPos);
                    this->_currentGame->finishTurn();
                }
            }
            this->_currentGame->setSelectedPiece(nullptr);
        }
    }
}