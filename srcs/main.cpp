#include "../includes/Equilattechess.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), WINDOW_TITLE);
    Menu mainMenu;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        mainMenu.drawMenu(&window);
        
    }

    return 0;
}