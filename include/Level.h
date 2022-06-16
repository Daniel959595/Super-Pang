#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Player.h"
#include "RegularBall.h"
#include "BreakableTile.h"
#include "CollisionHandling.h"

#include <fstream>

using BallsData = std::vector<std::shared_ptr<BaseBall>>;
using TilesData = std::vector<std::shared_ptr<BaseTile>>;

class Level
{
public:
	
	Level();

	void loadLevel            (int levelIndex);
	void resetLevel           (Situation& situation);
	void runLevel             (sf::RenderWindow& window, Situation& situation);

	void ballShot             (BaseBall& ball);

private:
	void setBackgroundRects   ();
	void setBackground        (int levelIndex);
	void setText              ();
	void setTextPos           ();
	void updateText           ();
	//void loadBalls            ();
	void loadFromfile         ();
	void openFile             (std::ifstream& in);
	void closeFile            (std::ifstream& in);
	void loadObjects          (std::ifstream& in);
	void addObj               (int objNum, float xCord, float yCord);
	void addBall			  (sf::Vector2f& pos, Resources::Objects ballType);
	void addTile			  (sf::Vector2f& pos, Resources::Objects tileType);
	void setPlayerPos         ();
	void setBorders           ();
	
	void draw                 (sf::RenderWindow& window);
	void handleEvents         (sf::RenderWindow& window, Situation& situation);
	void handleCollisions     ();
	void borderCollision      ();
	void update               ();
	void checkCollision       (GameObj& obj);
	void addItems             ();
	void addScore();
	void eraseDisposed        ();
	void checkLevelStatus     (Situation& situation);
	

public:

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<sf::IntRect> m_backgroundsRects;
	sf::RectangleShape m_borders;                       // represent the edges of the play ground.

	sf::Clock m_clock = sf::Clock();

	int m_levelIndex;
	sf::Text m_text;
	const sf::Font& m_font;

	CollisionHandling m_collisionHandler;

	Player m_player;
	BallsData m_balls;
	TilesData m_tiles;
	
	//std::vector<Gift> m_gifts;

	//sf::Sprite m_backGround;
};