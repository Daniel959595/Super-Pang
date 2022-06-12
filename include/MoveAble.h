#pragma once

#include "GameObj.h"

class MoveAble : public GameObj
{
public:
	MoveAble(Resources::Objects object, Direction dir, sf::Time animationTime);
	virtual ~MoveAble() = 0 {};

	virtual void update(sf::Time delta) = 0;
	virtual void borderCollision(sf::RectangleShape& border);
	//void direction(sf::Keyboard::Key key);
	virtual void analizeCollision(GameObj& other);

protected:
	virtual void moveInside(sf::RectangleShape& border);
	virtual void setDirection(Direction newDir);
	virtual void fixCollision(MixDirection newDir, const GameObj& other);
	MixDirection getCollisionSide(const GameObj& other);
public:

protected:
	//Animation m_animation;
	Direction m_dir;
	sf::Vector2f m_velocity;

	float m_speed;
};

