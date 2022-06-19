#include "Level.h"
#include "CollisionHandling.h"




const auto TextSize = 50;

Level::Level() 
	: m_texture(Resources::instance().texture(Resources::Objects::Backgrounds)), m_collisionHandler(*this),
	  m_font(Resources::instance().getFont()), m_music(NUM_MUSICS)
{
	m_sprite.setTexture(m_texture);
	setText();
	setBackgroundRects();
	setMusic();
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
	loadFromfile();
	//setPlayerPos();
}

void Level::loadFromfile()
{
	static std::ifstream in;
	openFile(in);
	loadObjects(in);
	closeFile(in);
}

void Level::openFile(std::ifstream& in)
{
	static std::string fileName;
    fileName = { "level_" + std::to_string(m_levelIndex) + ".txt" };
	
	in.open(fileName);
	if (!in) 
		m_levelIndex++;//exeption!
}

void Level::closeFile(std::ifstream& in)
{
	in.close();
}

void Level::loadObjects(std::ifstream& in)
{
	int objNum;
	float xCord, yCord;

	in >> objNum >> xCord >> yCord;
	while (in) {
		addObj(objNum, xCord, yCord);
		in >> objNum >> xCord >> yCord;
	}
}

void Level::addObj(int objNum, float xCord, float yCord)
{
	static sf::Vector2f pos;
	pos = { xCord,yCord };
	switch (objNum)
	{
	case Resources::Player:         setPlayerPos(); break;
	case Resources::RegularBall:    addBall(pos, Resources::Objects(objNum)); break;
	case Resources::TriangleBall:   addBall(pos, Resources::Objects(objNum)); break;
	case Resources::BreakableTile:  addTile(pos, Resources::Objects(objNum)); break;
	case Resources::ScoreGift:      addGift(pos, Resources::Objects(objNum)); break;
	default:
		break;
	}
}

void Level::addBall(sf::Vector2f& pos, Resources::Objects ballType)
{
	if (ballType == Resources::Objects::RegularBall)
		m_balls.emplace_back(std::shared_ptr<RegularBall>(new RegularBall(BallSize::Big, pos, Direction::Left, false)));
	else if (ballType == Resources::Objects::TriangleBall)
		m_balls.emplace_back(std::shared_ptr<TriangleBall>(new TriangleBall(BallSize::Big, pos, Direction::Left, false)));
}

void Level::addTile(sf::Vector2f& pos, Resources::Objects tileType)
{
	if (tileType == Resources::Objects::BreakableTile)
		m_tiles.emplace_back(std::shared_ptr<BreakableTile>(new BreakableTile(TileColor::Blue, TileSize::Big, pos, Direction::Stay)));
	//else
}

void Level::addGift(sf::Vector2f& pos, Resources::Objects giftType)
{
	if (giftType == Resources::ScoreGift)
		m_gifts.emplace_back(std::shared_ptr<ScoreGift>(new ScoreGift(pos, Direction::Stay)));
}

void Level::setBackground(int levelIndex)
{
	m_sprite.setTextureRect(m_backgroundsRects[levelIndex - 1]);//-1
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

void Level::setMusic()
{
	int i = 0;
	m_music[i++].openFromFile("LevelMusic1.wav");
	m_music[i++].openFromFile("LevelMusic2.wav");
	m_music[i++].openFromFile("LevelMusic3.wav");
}

void Level::handleMusic(bool toPlay)
{
	if (toPlay) {
		m_music[m_levelIndex % m_music.size()];
		m_music[m_levelIndex % m_music.size()].setLoop(true);
		m_music[m_levelIndex % m_music.size()].setVolume(50);
		m_music[m_levelIndex % m_music.size()].play();
	}
	else
		m_music[m_levelIndex % m_music.size()].stop();
}

void Level::updateText()
{
	m_text.setString("Level No." + std::to_string(m_levelIndex));
	setTextPos();
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
	handleMusic(true);
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
	for (auto& g : m_gifts) {
		(*g).draw(window);
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
	handleBallsCollision();
	
	checkCollision(m_player);
	for (auto& s : m_player.getShots()) {
		checkCollision(*s);
	}
	for (auto& g : m_gifts) {
		checkCollision(*g);
	}
}

void Level::handleBallsCollision()
{
	for (auto& b : m_balls) 
		for (auto& t : m_tiles) {
			(*b).setQuartes(*t);
		}
	for (auto& b : m_balls) {
		if ((*b).isCollide())
			(*b).fixCollision();
	}
	for (auto& b : m_balls) {
		(*b).setQuartes(m_player);
	}
	for (auto& b : m_balls)
		for (auto& s : m_player.getShots()) {
			if ((*b).isCollide(*s)) {
				m_collisionHandler.processCollision((*b), *s);
				break;
			}
		}
}

void Level::borderCollision()
{
	m_player.borderCollision(m_borders);
	for (auto& b : m_balls) {
		(*b).borderCollision(m_borders);
	}
	for (auto& g : m_gifts) {
		(*g).borderCollision(m_borders);
	}
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
	for (auto& g : m_gifts) {
		if (obj.checkCollision(*g)) {
			m_collisionHandler.processCollision(obj, *g);
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
		if (ball->isDisposed() && ball->getBallSize() != BallSize::Tiny) {
			ballShot(*ball);
			break;
		}
	}
}

void Level::addScore()
{
	for (auto& ball : m_balls) {
		if (ball->isDisposed()) {
			m_player.addScore(m_player.ballSizeToScore(ball->getBallSize()));
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
	std::erase_if(m_gifts, [](auto& gift)
		{
			return gift->isDisposed();
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
	for (auto& g : m_gifts) {
		(*g).update(delta);
	}
	m_player.update(delta);
	for (auto& t : m_tiles) {
		(*t).update(delta);
	}
}

void Level::resetLevel(Situation& situation)
{
	handleMusic(false);
	m_balls.clear();
	m_tiles.clear();
	m_player.resetPlayer(situation);
	m_gifts.clear();
}

void Level::ballShot(BaseBall& ball)
{
	//BaseBall& Ball  = dynamic_cast<BaseBall&>(ball);
	auto pair = ball.split();

	m_balls.push_back(pair.first);
	m_balls.push_back(pair.second);
}
