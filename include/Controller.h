#pragma once

#include "SFML/Graphics.hpp"

#include "Menu.h"
#include "Utilities.h"

class Controller
{
public:
	Controller();
	void runMenu();


private:
	void runGame();

public:


private:
	Menu m_menu;
	sf::RenderWindow m_window;
	sf::View m_view;
};