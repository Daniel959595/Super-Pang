#include "Controller.h"




Controller::Controller() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SUPER PANG!")
{
	m_window.setFramerateLimit(60);
	m_view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	m_view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
}

void Controller::runMenu()
{
	m_menu.handleMenu(m_window, m_view);
}

void Controller::runGame()
{
}
