#pragma once

#include "Equilattechess.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Menu
{
public:
    Menu();
    ~Menu();

    void drawMenu(sf::RenderWindow *window);
};