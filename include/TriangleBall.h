#pragma once


#include "BaseBall.h"


class TriangleBall : public BaseBall
{
public:
	TriangleBall(BallSize size, sf::Vector2f pos, Direction dir, bool isNewBall);

	virtual void update(sf::Time delta) override;
	virtual void moveInside(sf::RectangleShape& border) override;

	virtual pair split() override;
private:
	virtual void setVelocity(Direction dir, bool isNewBall) override;

};