#include "Controller.h"
#include <memory>
#include <functional>

#include <thread>


Controller::Controller() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SUPER PANG!"),
		m_font(Resources::instance().getFont())
{
	setInfo();
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
	m_returnToMenu = false;
	m_levelIndex = 1;
	while (m_window.isOpen() && m_levelIndex <= NUM_LEVELS) {
		m_situation = Situation::LevelRunnig;
		displayMessage(m_levelIndex, m_situation);
		m_levelsHandler.loadLevel(m_levelIndex);
		m_levelsHandler.runLevel(m_window, m_situation);
		handleSituation();
		if (m_returnToMenu) {
			return;
		}
	}
	m_situation = Situation::GameFinished;
	handleSituation();
}

void Controller::displayMessage(int levelIndex, Situation& situation)
{
	using namespace std::chrono_literals;

	setInfoData(levelIndex, situation);

	m_window.clear();
	m_window.draw(m_info);
	m_window.display();
	std::this_thread::sleep_for(3s);
}

void Controller::handleSituation() //switch!!!
{
	if (m_situation == Situation::LevelSucced)
	{
		m_levelIndex++;
	}
	else if (m_situation == Situation::EscKeyPressed)
		m_returnToMenu = true;
	else if (m_situation == Situation::LevelFailed)
		displayMessage(m_levelIndex, m_situation);
	else if (m_situation == Situation::GameOver) {
		displayMessage(m_levelIndex, m_situation);
		m_returnToMenu = true;
	}
	else if (m_situation == Situation::GameFinished) {
		displayMessage(m_levelIndex, m_situation);
		m_levelsHandler.resetLevel(m_situation);
		m_levelIndex = 1;
		m_returnToMenu = true;
	}
	
}

void Controller::setInfo()
{
	m_info.setFont(m_font);
	m_info.setCharacterSize(100);
	m_info.setFillColor(sf::Color::Black);
	m_info.setOutlineThickness(3);
	m_info.setOutlineColor(sf::Color{ 102,0,51 });
}

void Controller::setInfoData(int levelIndex, Situation& situation)
{
	float x, y;
	std::string level(std::to_string(levelIndex));
	std::string messege;

	switch (situation)
	{
	case Situation::LevelRunnig:   
	case Situation::LevelSucced:   messege = std::string("level number " + level); break;
	case Situation::LevelFailed:   messege = std::string("you faild! try again");  break;
	case Situation::GameFinished:  messege = std::string("Well done!");            break;
	case Situation::GameOver:      messege = std::string("Game Over!");            break;
	default: break;
	}
	m_info.setString(messege);

	x = (WINDOW_WIDTH - m_info.getGlobalBounds().width) / 2;
	y = (WINDOW_HEIGHT - m_info.getGlobalBounds().height) / 2 - (m_info.getGlobalBounds().height / 2);
	m_info.setPosition(sf::Vector2f(x, y));
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
	int i = 0, space = 15;
	float x = WINDOW_WIDTH / 2 - (BUTTON_WIDTH / 2);
	float y = WINDOW_HEIGHT / 2;

	sf::Vector2f pos = { x, y + (i++ * BUTTON_HEIGHT) + space};

	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "START", [&]() { this->runGame(); }))); 

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT) + space);
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "SCORE BOARD", [&]() { this->scoreBoard(); })));

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT) + space);
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "HELP", [&]() { this->help(); })));

	pos = sf::Vector2f(x, y + (i++ * BUTTON_HEIGHT) + space);
	m_menu.addButton(std::unique_ptr<BaseButton>(new Button(pos, "EXIT", [&]() { this->exitGame(); })));
}

