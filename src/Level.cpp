#include "Level.h"
#include "CollisionHandling.h"

Level::Level() 
	: m_texture(Resources::instance().texture(Resources::Objects::Backgrounds)), m_collisionHandler(*this)
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
	
	m_balls.emplace_back(std::shared_ptr<RegularBall>(new RegularBall(BallSize::Big, sf::Vector2f(x, y), Direction::Left, false)));
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
		addBalls();
		eraseDisposed();
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
		(*b).draw(window);
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
		case sf::Event::KeyPressed:
			m_player.handleEvents(event.key.code);
			break;
		}
	}
}

void Level::handleCollision()
{
	borderCollision();

	checkCollision(m_player);

	for (auto& b : m_balls) {
		checkCollision(*b);
	}

	for (auto& s : m_player.getShots()) {
		checkCollision(*s);
	}
}

void Level::borderCollision()
{
	for (auto& b : m_balls) {
		(*b).borderCollision(m_borders);
	}
	m_player.borderCollision(m_borders);
}

void Level::checkCollision(GameObj& obj)
{
	for (auto& b : m_balls) {
		if (obj.checkCollision(*b)) {
			m_collisionHandler.processCollision(obj, *b);
			break;
		}
	}
	for (auto& s : m_player.getShots()) {
		if (obj.checkCollision(*s)) {
			m_collisionHandler.processCollision(obj, *s);
			break;
		}
	}
}

void Level::addBalls()
{
	for (auto& ball : m_balls) {
		if (ball->isDisposed() && ball->getBallSize() != BallSize::Small) {
			ballShot(*ball);
			break;
		}
	}
}

void Level::eraseDisposed()
{
	std::erase_if(m_balls, [](auto& ball)
		{
			return ball->isDisposed();
		});
	std::erase_if(m_player.getShots(), [](auto& shot)
		{
			return shot->isDisposed();
		});
}

void Level::update()
{
	const auto delta = m_clock.restart();

	for (auto& b : m_balls) {
		(*b).update(delta);
	}
	m_player.update(delta);
}

void Level::ballShot(BaseBall& ball)
{
	//BaseBall& Ball  = dynamic_cast<BaseBall&>(ball);
	auto pair = ball.split();

	m_balls.push_back(pair.first);
	m_balls.push_back(pair.second);
}
