#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "MoveAble.h"


class Player : public MoveAble
{
public:
	Player();

	virtual void update(sf::Time delta);

	void dirFromKey();
	void direction(Direction dir);

	//void shoot(); 
private:
	bool m_faceRight = true;
	//std::vector<shoots> m_shoot(); guns?
};