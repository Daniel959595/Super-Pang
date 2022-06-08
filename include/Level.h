#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Player.h"
#include "BaseBall.h"
#include "RegularBall.h"
#include "CollisionHandling.h"

using BallsData = std::vector<std::shared_ptr<BaseBall>>;

class Level
{
public:
	
	Level();

	void loadLevel(int levelIndex);
	//void resetLevel();
	void runLevel(sf::RenderWindow& window);

	void ballShot(BaseBall& ball);

private:
	void setBackgroundRects();
	void setBackground(int levelIndex);
	void loadBalls();
	void setBorders();
	void draw(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window);
	void handleCollision();
	void borderCollision();
	void checkCollision(GameObj& obj);
	void addBalls();
	void eraseDisposed();
	void update();


public:

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<sf::IntRect> m_backgroundsRects;
	sf::RectangleShape m_borders;                       // represent the edges of the play ground.

	sf::Clock m_clock = sf::Clock();

	int m_levelIndex;

	CollisionHandling m_collisionHandler;

	Player m_player;
	BallsData m_balls;
	//std::vector<Ball> m_balls;
	//std::vector<Tile> m_tiles;
	//std::vector<Gift> m_gifts;

	//sf::Sprite m_backGround;
};