#pragma once

#include "SFML/Graphics.hpp"

#include "Utilities.h"
#include "MoveAble.h"
#include "RegularShot.h"

using ShotsData = std::vector<std::shared_ptr<BaseShot>>;

class Player : public MoveAble
{
public:
	Player();

	virtual void draw(sf::RenderWindow& window) override;
	virtual void update(sf::Time delta);

	void dirFromKey();
	void direction(Direction dir);
	void handleEvents(sf::Keyboard::Key key);

	virtual void borderCollision(sf::RectangleShape& border) override;

	ShotsData& getShots() { return m_shots; }

private:
	void shoot(); 
	void updateShots(sf::Time delta);

private:
	ShotType m_shot = ShotType::Normal;
	
	ShotsData m_shots;
};