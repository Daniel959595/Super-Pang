#include "Level.h"

Level::Level() 
	: m_texture(Resources::instance().texture(Resources::Objects::Backgrounds))
{
	m_sprite.setTexture(m_texture);
	setBackgroundRects();
}

void Level::setBackgroundRects()
{
	for (int i = 8; i < 25 * (208 + 8); i += 216) {
		m_backgroundsRects.push_back(sf::IntRect(8, i, 384, 208));
		m_backgroundsRects.push_back(sf::IntRect(400, i, 384, 208));
	}
}

void Level::loadLevel(int levelIndex)
{
	setBackground(levelIndex);
}

void Level::setBackground(int levelIndex)
{
	m_sprite.setTextureRect(m_backgroundsRects[levelIndex]);
	float factorX = WINDOW_WIDTH / m_sprite.getGlobalBounds().width;
	float factorY = BACBGROUND_HEIGHT / m_sprite.getGlobalBounds().height;
	m_sprite.setScale(factorX, factorY);
}

void Level::runLevel(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		draw(window);
		handleEvents(window);
		update(window);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_sprite);
	m_player.draw(window);
	//window.draw(m_backGround);
	/*for (auto& b : m_balls) {
		(b)->draw(window);
	}*/
	//tiles
	//...
	window.display();
}

void Level::handleEvents(sf::RenderWindow& window)
{
	for (auto event = sf::Event{}; window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		/*case sf::Event::KeyPressed:
			m_player.direction(event.key.code);
			break;*/
		}
	}
}

void Level::update(sf::RenderWindow& window)
{
	const auto delta = m_clock.restart();

	/*for (auto& b : m_balls) {

	}*/
	m_player.update(delta);
}
