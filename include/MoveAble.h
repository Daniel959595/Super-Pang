#pragma once

#include "GameObj.h"

class MoveAble : public GameObj
{
public:
	MoveAble(Resources::Objects object, Direction dir);
	~MoveAble() = 0 {};

	virtual void update(sf::Time delta) = 0;
	//void direction(sf::Keyboard::Key key);

protected:
	//Animation m_animation;
	float m_speed;
	Direction m_dir;
};

