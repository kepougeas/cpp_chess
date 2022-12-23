#include "../includes/Equilattechess.hpp"

Menu::Menu(sf::RenderWindow *window, int *state) {
    // Setting window pointer
    this->window = window;
    this->state = state;

    // Loading the fonts
    if (!this->fontTitle.loadFromFile(TITLE_FONT_PATH) 
    || !this->fontMenu.loadFromFile(MENU_FONT_PATH)) {
        printf("Could not load font");
        exit(-1);
    }

    // Creating the titles and menu entries
    this->title.setFont(this->fontTitle);
    this->title.setString(TITLE_TEXT);
    this->title.setCharacterSize(TITLE_TEXT_SIZE);
    this->title.setFillColor(sf::Color::Green);
    this->title.setOrigin(this->title.getGlobalBounds().width / 2 - 15, 0);
    this->title.setPosition(this->window->getSize().x / 2u, 0);

    this->playEntry.setFont(this->fontMenu);
    this->playEntry.setString(PLAY_TEXT);
    this->playEntry.setCharacterSize(MENU_TEXT_SIZE);
    this->playEntry.setFillColor(sf::Color::White);
    this->playEntry.setPosition((this->window->getSize().x / 2u) - (this->playEntry.getGlobalBounds().width / 2), 200);

    this->exitEntry.setFont(this->fontMenu);
    this->exitEntry.setString(EXIT_TEXT);
    this->exitEntry.setCharacterSize(MENU_TEXT_SIZE);
    this->exitEntry.setFillColor(sf::Color::White);
    this->exitEntry.setPosition((this->window->getSize().x / 2u) - (this->exitEntry.getGlobalBounds().width / 2), 300);
};

Menu::~Menu() {};

void Menu::drawMenu()
{
    this->window->draw(this->title);
    this->window->draw(this->playEntry);
    this->window->draw(this->exitEntry);

    this->checkClickEvents();
}

void Menu::checkClickEvents()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i clicPosition = sf::Mouse::getPosition(*this->window);
        sf::Vector2f playButtonPosition = this->playEntry.getPosition();
        sf::FloatRect playButtonSize = this->playEntry.getGlobalBounds();
        sf::Vector2f exitButtonPosition = this->exitEntry.getPosition();
        sf::FloatRect exitButtonSize = this->exitEntry.getGlobalBounds();

        // We clicked PLAY
        if ((clicPosition.x >= playButtonPosition.x && clicPosition.x <= (playButtonPosition.x + playButtonSize.width * 2))
        && (clicPosition.y >= playButtonPosition.y && clicPosition.y <= (playButtonPosition.y + playButtonSize.height * 2)))
        {
            *this->state = PLAY_STATE;
        }

        // We clicked EXIT
        else if ((clicPosition.x >= exitButtonPosition.x && clicPosition.x <= (exitButtonPosition.x + exitButtonSize.width * 2))
        && (clicPosition.y >= exitButtonPosition.y && clicPosition.y <= (exitButtonPosition.y + exitButtonSize.height * 2)))
        {
            *this->state = EXIT_STATE;
        }
    }
}