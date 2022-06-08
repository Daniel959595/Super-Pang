#pragma once


#include "BaseBall.h"


class RegularBall : public BaseBall
{
public:
	RegularBall(BallSize size, sf::Vector2f pos, Resources::Objects ballType, Direction dir);

	virtual pair split() override;
private:

};