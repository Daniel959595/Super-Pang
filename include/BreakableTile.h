#pragma once


#include "BaseTile.h"


class BreakableTile : public BaseTile
{
public:
	BreakableTile(TileColor color, TileSize size, sf::Vector2f pos, Direction dir);
	~BreakableTile() = default;
	
	virtual void setIsDisposed(bool status) override;
	virtual void update(sf::Time delta) override;

private:
	bool m_isBreaking = false;

	float m_updateTime = 0.02f;
	float m_toatalTime = 0.0f;
};