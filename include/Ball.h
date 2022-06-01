#pragma once

#include "MoveAble.h"



class Ball : public MoveAble
{
public:
	Ball(BallSize size, sf::Vector2f pos, Direction dir);

	virtual void update(sf::Time delta);

private:
	sf::Vector2f getScaleFactors(BallSize size) const;
	float getDesireSize(BallSize size) const;
	void setVelocity(Direction dir);

	virtual void moveInside(sf::RectangleShape& border);

public:


private:
	BallSize m_ballSize;

	sf::Vector2f m_velocity;
	float m_gravity = 1.f;
	float m_moveTime = 0.02f;
	float m_toatalTime = 0.0f;
};


