#pragma once

#include "MoveAble.h"


class BaseBall : public MoveAble
{
public:
	BaseBall(BallSize size, sf::Vector2f pos, Resources::Objects ballType, Direction dir, bool isNewBall);
	virtual ~BaseBall() = 0 {};

	virtual void update(sf::Time delta);

	using pair = std::pair<std::shared_ptr<BaseBall>, std::shared_ptr<BaseBall>>;
	virtual pair split() = 0;
	BallSize getBallSize() const;

	virtual bool isCollide(const GameObj& other); //override;
	virtual void fixCollision(const GameObj& other) override;

protected:
	sf::Vector2f getScaleFactors(BallSize size) const;
	float getDesireSize(BallSize size) const;
	sf::Color getRandColor() const;
	void setVelocity(Direction dir, bool isNewBall);

	float maxVelocity(BallSize size);
	virtual void moveInside(sf::RectangleShape& border);

	virtual bool analizeCollision(const GameObj& other) override;
	virtual bool getNewDirect(const GameObj& other);
	bool isInRadius(const GameObj& other);
	bool checkDistance(const sf::Vector2f corner);

	BallSize getSmallerSize();

public:


protected:
	BallSize m_ballSize;

	//sf::Vector2f m_velocity;
	float m_gravity = 1.f;
	float m_moveTime = 0.02f;
	float m_toatalTime = 0.0f;

	MixDirection m_newDirection;
	bool m_newBall = false;    // i.e. if it was exist from the begining.
};


