#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Player.h"


class Level
{
public:
	
	Level();

	void loadLevel(int levelIndex);
	//void resetLevel();
	void runLevel(sf::RenderWindow& window);

private:
	void setBackgroundRects();
	void setBackground(int levelIndex);
	void draw(sf::RenderWindow& window);
	void handleEvents(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);


public:

private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<sf::IntRect> m_backgroundsRects;

	sf::Clock m_clock = sf::Clock();

	int m_levelIndex;

	Player m_player;
	//std::vector<Ball> m_balls;
	//std::vector<Tile> m_tiles;
	//std::vector<Gift> m_gifts;

	//sf::Sprite m_backGround;
};