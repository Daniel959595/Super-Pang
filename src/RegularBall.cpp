#include "RegularBall.h"

//using pair = std::pair<std::shared_ptr<BaseBall>, std::shared_ptr<BaseBall>>;


RegularBall::RegularBall(BallSize size, sf::Vector2f pos, Direction dir, bool newBall)
	: BaseBall(size, pos, Resources::Objects::RegularBall, dir, newBall)
{
}

RegularBall::pair RegularBall::split()
{
	if (!this->isDisposed())
		return pair(); // exeption!!!

	auto first  = std::make_shared<RegularBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Left, true);
	auto second = std::make_shared<RegularBall>(getSmallerSize(), m_sprite.getPosition(), Direction::Right, true);
    pair newBalls(first, second);

	return newBalls;
}