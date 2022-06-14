#include "Level.h"
#include "CollisionHandling.h"

const auto TextSize = 50;

Level::Level() 
	: m_texture(Resources::instance().texture(Resources::Objects::Backgrounds)), m_collisionHandler(*this),
	  m_font(Resources::instance().getFont())
{
	m_sprite.setTexture(m_texture);
	setText();
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
	m_levelIndex = levelIndex;
	setBackground(levelIndex);
	updateText();
	loadBalls();
	setPlayerPos();
}

void Level::setBackground(int levelIndex)
{
	m_sprite.setTextureRect(m_backgroundsRects[levelIndex]);
	if (m_sprite.getScale() == sf::Vector2f(1, 1)) {
		float factorX = WINDOW_WIDTH / m_sprite.getGlobalBounds().width;
		float factorY = BACBGROUND_HEIGHT / m_sprite.getGlobalBounds().height;
		m_sprite.setScale(factorX, factorY);
	}
}

void Level::setText()
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(TextSize);
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineThickness(2);
	m_text.setOutlineColor(sf::Color{ 0,150,80 });
}

void Level::setTextPos()
{
	float x = (WINDOW_WIDTH / 2) - (m_text.getGlobalBounds().width / 2);
	float y = BACBGROUND_HEIGHT + ((WINDOW_HEIGHT - BACBGROUND_HEIGHT) - (m_text.getGlobalBounds().height)) / 2;
	m_text.setPosition(sf::Vector2f(x, y));
}

void Level::updateText()
{
	m_text.setString("Level No." + std::to_string(m_levelIndex));
	setTextPos();
}

void Level::loadBalls()
{
	float x = (BACBGROUND_WIDTH / 2) - (BIG_BALL_SIZE / 2);
	float y = BACBGROUND_HEIGHT / 3 - (BIG_BALL_SIZE / 2);

	auto pos = sf::Vector2f(x, y);
	m_balls.emplace_back(std::shared_ptr<RegularBall>(new RegularBall(BallSize::Big, pos, Direction::Left, false)));

	/*for (int i = 0; i < (int)BACBGROUND_WIDTH / MEDIUM_TILE_SIZE; i++) {
		pos = sf::Vector2f(FRAME_WIDTH + (i * MEDIUM_TILE_SIZE), (BACBGROUND_HEIGHT / 3) * 2);
		m_tiles.emplace_back(std::shared_ptr<BreakableTile>(new BreakableTile(TileColor::Blue, TileSize::Big, pos, Direction::Stay)));
	}*/
}

void Level::setPlayerPos()
{
	float x = (WINDOW_WIDTH / 2) - (PLAYER_WIDTH / 2);
	float y = BACBGROUND_HEIGHT  -  PLAYER_HIEGHT - FRAME_WIDTH;
	
	auto pos = sf::Vector2f(x, y);
	m_player.setPos(pos);
}

void Level::setBorders()
{
	m_borders.setPosition(sf::Vector2f(0.0f + FRAME_WIDTH, 0.0f + FRAME_WIDTH));
	m_borders.setSize(sf::Vector2f(BACBGROUND_WIDTH - (FRAME_WIDTH * 2), BACBGROUND_HEIGHT - (FRAME_WIDTH * 2)));
	m_borders.setFillColor(sf::Color::Transparent);
}

void Level::runLevel(sf::RenderWindow& window, Situation& situation)
{
	while (window.isOpen()) {
		draw(window);
		handleEvents(window, situation);
		update();
		handleCollisions();
		addItems();
		addScore();
		eraseDisposed();
		checkLevelStatus(situation);
		if (situation != Situation::LevelRunnig) {
			resetLevel(situation);
			return;
		}
	}
}

void Level::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_text);
	window.draw(m_sprite);
	window.draw(m_borders);
	//window.draw(m_backGround);
	for (auto& b : m_balls) {
		(*b).draw(window);
	}
	for (auto& t : m_tiles) {
		(*t).draw(window);
	}
	m_player.draw(window);
	window.display();
}

void Level::handleEvents(sf::RenderWindow& window, Situation& situation)
{
	for (auto event = sf::Event{}; window.pollEvent(event); )
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				situation = Situation::EscKeyPressed;
				break;
			}
			else {
				m_player.handleEvents(event.key.code);
				break;
			}
		}
	}
}

void Level::handleCollisions()
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
	for (auto& t : m_tiles) {
		if (obj.checkCollision(*t)) {
			m_collisionHandler.processCollision(obj, *t);
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

void Level::addItems()
{
	for (auto& ball : m_balls) {
		if (ball->isDisposed() && ball->getBallSize() != BallSize::Small) {
			ballShot(*ball);
			break;
		}
	}
}

void Level::addScore()
{
	for (auto& ball : m_balls) {
		if (ball->isDisposed()) {
			m_player.addScore(ball->getBallSize());
		}
	}
}

void Level::eraseDisposed()
{
	std::erase_if(m_balls, [](auto& ball)
		{
			return ball->isDisposed();
		});
	std::erase_if(m_tiles, [](auto& tile)
		{
			return tile->isDisposed();
		});
	std::erase_if(m_player.getShots(), [](auto& shot)
		{
			return shot->isDisposed();
		});
}

void Level::checkLevelStatus(Situation& situation)
{
	if (!m_player.isLeftLives())
		situation = Situation::GameOver;
	else if (m_player.isDisposed())
		situation = Situation::LevelFailed;
	else if (m_balls.empty())
		situation = Situation::LevelSucced;
}

void Level::update()
{
	const auto delta = m_clock.restart();

	for (auto& b : m_balls) {
		(*b).update(delta);
	}
	m_player.update(delta);
	for (auto& t : m_tiles) {
		(*t).update(delta);
	}
}

void Level::resetLevel(Situation& situation)
{
	m_balls.clear();
	m_tiles.clear();
	m_player.resetPlayer(situation);
}

void Level::ballShot(BaseBall& ball)
{
	//BaseBall& Ball  = dynamic_cast<BaseBall&>(ball);
	auto pair = ball.split();

	m_balls.push_back(pair.first);
	m_balls.push_back(pair.second);
}
