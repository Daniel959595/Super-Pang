#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Animation.h"



class GameObj
{
public:
	GameObj();
	//GameObj(Resources::Objects object, Direction dir);
	virtual ~GameObj() = 0 {};

	virtual void draw(sf::RenderWindow& window);

protected:

public:

protected:
	sf::Sprite m_sprite;
	//Animation m_animation;
};