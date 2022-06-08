#pragma once


#include "BaseBall.h"


class RegularBall : public BaseBall
{
public:
	RegularBall(BallSize size, sf::Vector2f pos, Direction dir, bool newBall);

	virtual pair split() override;
private:

};