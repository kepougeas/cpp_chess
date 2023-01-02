#pragma once

#include "Equilattechess.hpp"

#define AKIRA_FONT_PATH "./fonts/akira_font.otf"

#define TITLE_TEXT_SIZE 55
#define MENU_TEXT_SIZE 45

#define TITLE_TEXT "Welcome to Equi Latte Chess !"
#define PLAY_TEXT "PLAY"
#define EXIT_TEXT "EXIT"

class Menu
{
public:
    Menu(sf::RenderWindow *, int *);
    ~Menu() = default;

    void drawMenu();
    void checkClickEvents();

 private:
    sf::RenderWindow *_window;
    int *_state;

    sf::Font _fontTitle;
    sf::Font _fontMenu;

    sf::Text _title;
    sf::Text _playEntry;
    sf::Text _exitEntry;
};