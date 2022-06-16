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

	void setQuartes(const GameObj& other);
	virtual bool isCollide() const;
	virtual bool isCollide(const GameObj& other) const override;
	virtual void fixCollision();

protected:
	sf::Vector2f getScaleFactors(BallSize size) const;
	float getDesireSize(BallSize size) const;
	sf::Color getRandColor() const;
	void setVelocity(Direction dir, bool isNewBall);

	float maxVelocity(BallSize size);
	virtual void moveInside(sf::RectangleShape& border);

	virtual void analizeCollision(const GameObj& other) override;
	//virtual bool getNewDirect(const GameObj& other);
	virtual MixDirection getNewDirect();
	void setQuartesPos();
	void checkQuartes(const GameObj& other);

	bool isInRadius(const GameObj& other, TileCorner corner);
	bool checkDistance(const sf::Vector2f corner);

	BallSize getSmallerSize();

public:


protected:
	BallSize m_ballSize;

	float m_gravity = 1.f;
	float m_moveTime = 0.02f;
	float m_toatalTime = 0.0f;

	// represent the quarters that 
	// collide with other obj.
	int m_quarters[4] = {};

	sf::FloatRect fstQurter;
	sf::FloatRect scdQurter;
	sf::FloatRect trdQurter;
	sf::FloatRect frtQurter;

	bool m_isCollide = false;
	
	// if it was exist in the file or added later.
	bool m_newBall = false;      

	MixDirection m_newDirection;
};


