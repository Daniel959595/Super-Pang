#include "Controller.h"
#include <memory>
#include <functional>



Controller::Controller() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SUPER PANG!")
{
	m_window.setFramerateLimit(60);
	m_view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	m_view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	addButtons();
}

void Controller::runMenu()
{
	m_menu.handleMenu(m_window, m_view);
}

void Controller::runGame()
{
	int levelIndex = 0;
	while (m_window.isOpen() && ++levelIndex <= NUM_LEVELS) {
		m_levelsHandler.loadLevel(levelIndex);
		m_levelsHandler.runLevel(m_window);
	}
}

void Controller::scoreBoard()
{

}

void Controller::help()
{

}

void Controller::exitGame()
{
	exit(0);
}

void Controller::addButtons()
{
	int i = 0;
	float x = WINDOW_WIDTH / 2 - (BUTTON_WIDTH / 2);
	float y = WINDOW_HEIGHT / 2;

	sf::Vector2f pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT));

	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "START", [&]() { this->runGame(); }))); 

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT));
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "SCORE BOARD", [&]() { this->scoreBoard(); })));

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT));
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "HELP", [&]() { this->help(); })));

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT));
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "EXIT", [&]() { this->exitGame(); })));

}
