#include "Level.h"

Level::Level() 
	: m_texture(Resources::instance().texture(Resources::Objects::Backgrounds))
{
	m_sprite.setTexture(m_texture);
	setBackgroundRects();
	setBorders();
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
	loadBalls();
}

void Level::setBackground(int levelIndex)
{
	m_sprite.setTextureRect(m_backgroundsRects[levelIndex]);
	float factorX = WINDOW_WIDTH / m_sprite.getGlobalBounds().width;
	float factorY = BACBGROUND_HEIGHT / m_sprite.getGlobalBounds().height;
	m_sprite.setScale(factorX, factorY);
}

void Level::loadBalls()
{
	float x = (BACBGROUND_WIDTH / 2) - (BIG_BALL_SIZE / 2);
	float y = BACBGROUND_HEIGHT / 3 - (BIG_BALL_SIZE / 2);
	Ball ball(BallSize::Big, sf::Vector2f(x, y), Direction::Left);
	m_balls.push_back(ball);
}

void Level::setBorders()
{
	m_borders.setPosition(sf::Vector2f(0.0f + FRAME_WIDTH, 0.0f + FRAME_WIDTH));
	m_borders.setSize(sf::Vector2f(BACBGROUND_WIDTH - (FRAME_WIDTH * 2), BACBGROUND_HEIGHT - (FRAME_WIDTH * 2)));
	m_borders.setFillColor(sf::Color::Transparent);
}

void Level::runLevel(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		draw(window);
		handleEvents(window);
		update();
		handleCollision();
	}
}

void Level::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_sprite);
	window.draw(m_borders);
	m_player.draw(window);
	//window.draw(m_backGround);
	for (auto& b : m_balls) {
		b.draw(window);
	}
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

void Level::handleCollision()
{
	borderCollision();
}

void Level::borderCollision()
{
	for (auto& b : m_balls) {
		b.borderCollision(m_borders);
	}
	m_player.borderCollision(m_borders);
}

void Level::update()
{
	const auto delta = m_clock.restart();

	for (auto& b : m_balls) {
		b.update(delta);
	}
	m_player.update(delta);
}
