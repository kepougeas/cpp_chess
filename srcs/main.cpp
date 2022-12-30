#include "../includes/Equilattechess.hpp"
#include <cstdio>
#include <cstring>

void placeAllPieces(Game *game)
{
    // Creating and placing all pieces to the Game
    // WHITE
    class King *whiteKing = new class King(game, WHITE, {.x=7, .y=4});
    game->addPiece(whiteKing);
    class Queen *whiteQueen = new class Queen(game, WHITE, {.x=7, .y=3});
    game->addPiece(whiteQueen);
    class Bishop *whiteBishopOne = new class Bishop(game, WHITE, {.x=7, .y=2});
    game->addPiece(whiteBishopOne);
    class Bishop *whiteBishopTwo = new class Bishop(game, WHITE, {.x=7, .y=5});
    game->addPiece(whiteBishopTwo);
    class Knight *whiteKnightOne = new class Knight(game, WHITE, {.x=7, .y=1});
    game->addPiece(whiteKnightOne);
    class Knight *whiteKnightTwo = new class Knight(game, WHITE, {.x=7, .y=6});
    game->addPiece(whiteKnightTwo);
    class Rook *whiteRookOne = new class Rook(game, WHITE, {.x=7, .y=0});
    game->addPiece(whiteRookOne);
    class Rook *whiteRookTwo = new class Rook(game, WHITE, {.x=7, .y=7});
    game->addPiece(whiteRookTwo);
    for (int i = 0; i < 8; i++) {
        class Pawn *whitePawn;
        whitePawn = new class Pawn(game, WHITE, {.x=6, .y=i});
        game->addPiece(whitePawn);
    }

    // BLACK
    class King *blackKing = new class King(game, BLACK, {.x=0, .y=4});
    game->addPiece(blackKing);
    class Queen *blackQueen = new class Queen(game, BLACK, {.x=0, .y=3});
    game->addPiece(blackQueen);
    class Bishop *blackBishopOne = new class Bishop(game, BLACK, {.x=0, .y=2});
    game->addPiece(blackBishopOne);
    class Bishop *blackBishopTwo = new class Bishop(game, BLACK, {.x=0, .y=5});
    game->addPiece(blackBishopTwo);
    class Knight *blackKnightOne = new class Knight(game, BLACK, {.x=0, .y=1});
    game->addPiece(blackKnightOne);
    class Knight *blackKnightTwo = new class Knight(game, BLACK, {.x=0, .y=6});
    game->addPiece(blackKnightTwo);
    class Rook *blackRookOne = new class Rook(game, BLACK, {.x=0, .y=0});
    game->addPiece(blackRookOne);
    class Rook *blackRookTwo = new class Rook(game, BLACK, {.x=0, .y=7});
    game->addPiece(blackRookTwo);
    for (int i = 0; i < 8; i++) {
        class Pawn *blackPawn;
        blackPawn = new class Pawn(game, BLACK, {.x=1, .y=i});
        game->addPiece(blackPawn);
    }
}

int main(int argc, char **argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    int state = MENU_STATE;
    Menu mainMenu(&window, &state);
    Game *currGame = new Game();
    Board currBoard(&window, currGame, &state);
    placeAllPieces(currGame);
    bool debug = argc > 1 && strcmp(argv[1], "-d") == 0;

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // state is updated by Menu and Game instances
        if (state == MENU_STATE) {
            mainMenu.drawMenu();
        }
        else if (state == PLAY_STATE) {
            if (debug) {
                printf("PLAY STATE\n");
                currGame->printAllPieces();
            }
            currBoard.drawBoard();
        }
        else if (state == EXIT_STATE) {
            window.close();
        }
        window.display();
    }

    delete currGame;

    return 0;
}