#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "Animation.h"



class GameObj
{
public:
	//GameObj();
	GameObj(Resources::Objects object, Direction dir, sf::Time animationTime);
	virtual ~GameObj() = 0 {};

	virtual void draw(sf::RenderWindow& window);
	virtual void update(sf::Time delta) = 0;

	virtual bool checkCollision(const GameObj& other) ;   // call to other.isCollide(). const
	virtual bool isCollide(const GameObj& other) const;

	const sf::FloatRect& getGlobalBounds() const { return m_sprite.getGlobalBounds(); }

	virtual void setIsDisposed(bool status) { m_isDisposed = status; }
	bool isDisposed() { return m_isDisposed; }

protected:

public:

protected:
	sf::Sprite m_sprite;

	Animation m_animation;
	bool m_isDisposed = false;
};