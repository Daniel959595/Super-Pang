#pragma once

#include "GameObj.h"

class Unmovable : public GameObj
{
public:
	Unmovable(Resources::Objects object, Direction dir, sf::Time animationTime);
	virtual ~Unmovable() = 0 {};

	virtual void update(sf::Time delta) = 0;

protected:

public:

protected:
	
};

