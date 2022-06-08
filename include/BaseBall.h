#pragma once

#include "MoveAble.h"


class BaseBall : public MoveAble
{
public:
	BaseBall(BallSize size, sf::Vector2f pos, Resources::Objects ballType, Direction dir);
	~BaseBall() = 0 {};

	virtual void update(sf::Time delta);

	using pair = std::pair<std::shared_ptr<BaseBall>, std::shared_ptr<BaseBall>>;
	virtual pair split() = 0;

protected:
	sf::Vector2f getScaleFactors(BallSize size) const;
	float getDesireSize(BallSize size) const;
	sf::Color getRandColor() const;
	void setVelocity(Direction dir);

	float maxVelocity(BallSize size);
	virtual void moveInside(sf::RectangleShape& border);

public:


protected:
	BallSize m_ballSize;

	sf::Vector2f m_velocity;
	float m_gravity = 1.f;
	float m_moveTime = 0.02f;
	float m_toatalTime = 0.0f;
};


