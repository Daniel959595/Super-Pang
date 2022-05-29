#pragma once

#include "SFML/Graphics.hpp"

#include "Menu.h"
#include "Level.h"
#include "Utilities.h"
#include "Button.h"

class Controller
{
public:
	Controller();
	void runMenu();


private:
	void addButtons();
	void runGame();
	void scoreBoard();
	void help();
	void exitGame();

public:


private:
	Menu m_menu;
	Level m_levelsHandler;

	sf::RenderWindow m_window;
	sf::View m_view;
};