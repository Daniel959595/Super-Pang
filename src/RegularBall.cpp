#include "RegularBall.h"

using pair = std::pair<std::shared_ptr<BaseBall>, std::shared_ptr<BaseBall>>;


RegularBall::RegularBall(BallSize size, sf::Vector2f pos, Resources::Objects ballType, Direction dir)
	: BaseBall(size, pos, ballType, dir)
{
}

pair RegularBall::split()
{
	return pair();
}
