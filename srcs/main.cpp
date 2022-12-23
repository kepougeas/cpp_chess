#include "../includes/Equilattechess.hpp"

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
        else if (state == PLAY_STATE)
        {
            printf("PLAY STATE\n");
            window.close();
        }
        else if (state == EXIT_STATE)
        {
            window.close();
        }

        window.display();
    }

    return 0;
}