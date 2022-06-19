#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Player.h"
#include "RegularBall.h"
#include "TriangleBall.h"
#include "BreakableTile.h"
#include "ScoreGift.h"
#include "ShotGift.h"
#include "LifeGift.h"
#include "CollisionHandling.h"

#include <fstream>

using BallsData = std::vector<std::shared_ptr<BaseBall>>;
using TilesData = std::vector<std::shared_ptr<BaseTile>>;
using GiftsData = std::vector<std::shared_ptr<BaseGift>>;

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
	void setMusic             ();
	void handleMusic          (bool toPlay);
	void updateText           ();
	//void loadBalls            ();
	void loadFromfile         ();
	void openFile             (std::ifstream& in);
	void closeFile            (std::ifstream& in);
	void loadObjects          (std::ifstream& in);
	void addObj               (int objNum, float xCord, float yCord);
	void addBall			  (sf::Vector2f& pos, Resources::Objects ballType);
	void addTile			  (sf::Vector2f& pos, Resources::Objects tileType);
	void addGift			  (sf::Vector2f& pos);
	bool isDeserveGift        ();
	int  getRandGift          ();
	void setPlayerPos         ();
	void setBorders           ();
	
	void draw                 (sf::RenderWindow& window);
	void handleEvents         (sf::RenderWindow& window, Situation& situation);
	void handleCollisions     ();
	void handleBallsCollision ();
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

	std::vector<sf::Music> m_music;

	int m_levelIndex;
	sf::Text m_text;
	const sf::Font& m_font;

	CollisionHandling m_collisionHandler;

	Player m_player;
	BallsData m_balls;
	TilesData m_tiles;
	GiftsData m_gifts;

};