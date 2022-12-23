#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>

#include "Board.hpp"
#include "Game.hpp"
#include "Menu.hpp"

#define WINDOW_TITLE "Equi Latte Chess"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1024
#define MENU_STATE 1
#define PLAY_STATE 2
#define EXIT_STATE 3