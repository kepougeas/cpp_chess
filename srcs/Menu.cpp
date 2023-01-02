#include "../includes/Equilattechess.hpp"

Menu::Menu(sf::RenderWindow *window, int *state)
{
    // Setting window pointer
    this->_window = window;
    this->_state = state;

    // Loading the fonts
    if (!this->_fontTitle.loadFromFile(AKIRA_FONT_PATH) 
    || !this->_fontMenu.loadFromFile(AKIRA_FONT_PATH)) {
        printf("Could not load font");
        exit(-1);
    }

    // Creating the titles and menu entries
    this->_title.setFont(this->_fontTitle);
    this->_title.setString(TITLE_TEXT);
    this->_title.setCharacterSize(TITLE_TEXT_SIZE);
    this->_title.setFillColor(sf::Color::Green);
    this->_title.setOrigin(this->_title.getGlobalBounds().width / 2 - 15, 0);
    this->_title.setPosition(this->_window->getSize().x / 2u, 0);

    this->_playEntry.setFont(this->_fontMenu);
    this->_playEntry.setString(PLAY_TEXT);
    this->_playEntry.setCharacterSize(MENU_TEXT_SIZE);
    this->_playEntry.setFillColor(sf::Color::White);
    this->_playEntry.setPosition((this->_window->getSize().x / 2u) - (this->_playEntry.getGlobalBounds().width / 2), 200);

    this->_exitEntry.setFont(this->_fontMenu);
    this->_exitEntry.setString(EXIT_TEXT);
    this->_exitEntry.setCharacterSize(MENU_TEXT_SIZE);
    this->_exitEntry.setFillColor(sf::Color::White);
    this->_exitEntry.setPosition((this->_window->getSize().x / 2u) - (this->_exitEntry.getGlobalBounds().width / 2), 300);
};

void Menu::drawMenu()
{
    this->_window->draw(this->_title);
    this->_window->draw(this->_playEntry);
    this->_window->draw(this->_exitEntry);

    this->checkClickEvents();
}

void Menu::checkClickEvents()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i clicPosition = sf::Mouse::getPosition(*this->_window);
        sf::Vector2f playButtonPosition = this->_playEntry.getPosition();
        sf::FloatRect playButtonSize = this->_playEntry.getGlobalBounds();
        sf::Vector2f exitButtonPosition = this->_exitEntry.getPosition();
        sf::FloatRect exitButtonSize = this->_exitEntry.getGlobalBounds();

        // We clicked PLAY
        if ((clicPosition.x >= playButtonPosition.x && clicPosition.x <= (playButtonPosition.x + playButtonSize.width * 2))
        && (clicPosition.y >= playButtonPosition.y && clicPosition.y <= (playButtonPosition.y + playButtonSize.height * 2)))
        {
            *this->_state = PLAY_STATE;
        }

        // We clicked EXIT
        else if ((clicPosition.x >= exitButtonPosition.x && clicPosition.x <= (exitButtonPosition.x + exitButtonSize.width * 2))
        && (clicPosition.y >= exitButtonPosition.y && clicPosition.y <= (exitButtonPosition.y + exitButtonSize.height * 2)))
        {
            *this->_state = EXIT_STATE;
        }
    }
}