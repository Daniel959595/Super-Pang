#pragma once

#include "Unmovable.h"


class BaseTile : public Unmovable
{
public:
	BaseTile(TileColor color, TileSize size, sf::Vector2f pos, Resources::Objects TileType, Direction dir);
	virtual ~BaseTile() = 0 {};

	virtual void update(sf::Time delta) override = 0;
	//virtual void activateSound() override;

protected:
	sf::Color getColor(TileColor color);
	sf::Vector2f getScaleFactors(TileSize size) const;
	float getDesireSize(TileSize size) const;
public:


protected:
	Resources::Objects m_tileType;

};

