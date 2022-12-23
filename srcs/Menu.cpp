#include "../includes/Equilattechess.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Menu::Menu() {};

Menu::~Menu() {};

void Menu::drawMenu(sf::RenderWindow *window)
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    window->clear();
    window->draw(shape);
    window->display();
}