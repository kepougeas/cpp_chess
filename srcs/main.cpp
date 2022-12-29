#include "../includes/Equilattechess.hpp"
#include <cstdio>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    int state = MENU_STATE;
    Menu mainMenu(&window, &state);

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
            printf("PLAY STATE\n");
            Game currGame;
            class Pawn pawnOne(&currGame, WHITE, {.x=4,.y=4});
            class Pawn pawnTwo(&currGame, BLACK, {.x=0,.y=2});

            class Bishop bishopOne(&currGame, WHITE, {.x=2, .y=2});

            class Rook rookOne(&currGame, WHITE, {.x=3, .y=4});

            class Knight knightOne(&currGame, BLACK, {.x=3, .y=3});

            class Queen queenElizabeth(&currGame, WHITE, {.x=3, .y=2});
            
            currGame.addPiece(&pawnOne);
            currGame.addPiece(&pawnTwo);
            currGame.addPiece(&bishopOne);
            currGame.addPiece(&rookOne);
            currGame.addPiece(&knightOne);
            currGame.addPiece(&queenElizabeth);

            pawnOne.printPosition();
            pawnOne.printPossibleMoves();
            pawnTwo.printPosition();
            pawnTwo.printPossibleMoves();
            bishopOne.printPosition();
            bishopOne.printPossibleMoves();
            rookOne.printPosition();
            rookOne.printPossibleMoves();
            knightOne.printPosition();
            knightOne.printPossibleMoves();
            queenElizabeth.printPosition();
            queenElizabeth.getPossibleMoves();

            //bishopOne.move({.x=3, .y=3});
            queenElizabeth.move({.x=3, .y=3});

            currGame.printAllPieces();

            window.close();
        }
        else if (state == EXIT_STATE) {
            window.close();
        }

        window.display();
    }

    return 0;
}