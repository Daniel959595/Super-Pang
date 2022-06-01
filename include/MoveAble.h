#pragma once

#include "GameObj.h"

class MoveAble : public GameObj
{
public:
	MoveAble(Resources::Objects object, Direction dir);
	~MoveAble() = 0 {};

	virtual void update(sf::Time delta) = 0;
	virtual void borderCollision(sf::RectangleShape& border);
	//void direction(sf::Keyboard::Key key);

protected:
	virtual void moveInside(sf::RectangleShape& border);

public:

protected:
	Animation m_animation;
	Direction m_dir;

	float m_speed;
};

