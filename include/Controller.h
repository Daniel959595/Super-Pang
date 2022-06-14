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
	void displayMessage(int levelIndex, Situation& situation);
	void setInfo();
	void setInfoData(int levelIndex, Situation& situatio);
	void runGame();
	void scoreBoard();
	void help();
	void exitGame();

	void handleSituation();

public:


private:
	Menu m_menu;
	Level m_levelsHandler;

	sf::RenderWindow m_window;
	sf::View m_view;

	sf::Text m_info;
	const sf::Font& m_font;

	int m_levelIndex = 1;
	Situation m_situation;
	bool m_returnToMenu;
};