#pragma once

#include "Equilattechess.hpp"

#define TITLE_FONT_PATH "./fonts/AntipastoPro-Bold_trial.ttf"
#define MENU_FONT_PATH "./fonts/AntipastoPro-Medium_trial.ttf"

#define TITLE_TEXT_SIZE 100
#define MENU_TEXT_SIZE 65

#define TITLE_TEXT "Welcome to Equi Latte Chess !"
#define PLAY_TEXT "PLAY"
#define EXIT_TEXT "EXIT"

class Menu
{
public:
    Menu(sf::RenderWindow *window, int *state);
    ~Menu();

    void drawMenu();
    void checkClickEvents();

 private:
    sf::RenderWindow *window;
    int *state;

    sf::Font fontTitle;
    sf::Font fontMenu;

    sf::Text title;
    sf::Text playEntry;
    sf::Text exitEntry;
};