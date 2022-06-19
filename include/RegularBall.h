#pragma once


#include "BaseBall.h"


class RegularBall : public BaseBall
{
public:
	RegularBall(BallSize size, sf::Vector2f pos, Direction dir, bool isNewBall);

	virtual void update(sf::Time delta) override;

	virtual pair split() override;
private:
	virtual void setVelocity(Direction dir, bool isNewBall) override;
};