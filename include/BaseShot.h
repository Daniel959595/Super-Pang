#pragma once

#include "SFML/Graphics.hpp"
#include "Utilities.h"

#include "MoveAble.h"

class BaseShot : public MoveAble
{
public:
	BaseShot(const sf::Vector2f& playerPos, Resources::Objects shotType); // & ?
	virtual ~BaseShot() = 0 {};

	virtual void update(sf::Time deltaTime) override;

protected:
	void setPosition(const sf::Vector2f& pos);
	 

public:


protected:
	sf::Time m_elapsed = {};

	//sf::Sound m_sound;

};