#pragma once

#include "GameObj.h"

class MoveAble : public GameObj
{
public:
	MoveAble(Resources::Objects object, Direction dir, sf::Time animationTime);
	virtual ~MoveAble() = 0 {};

	//virtual void update(sf::Time delta) = 0;
	virtual void borderCollision(sf::RectangleShape& border);
	//void direction(sf::Keyboard::Key key);
	virtual void analizeCollision(const GameObj& other) {};
	virtual void fixCollision(const GameObj& other) {};

protected:
	virtual void moveInside(sf::RectangleShape& border);
	virtual void setDirection(Direction newDir);
	//virtual MixDirection getCollisionSide(const GameObj& other) {};
public:

protected:
	//Animation m_animation;
	Direction m_dir;
	sf::Vector2f m_velocity;

	float m_speed;
};

