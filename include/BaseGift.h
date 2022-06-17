#pragma once

#include "MoveAble.h"


class BaseGift : public MoveAble {
public:

	BaseGift(sf::Vector2f pos, Resources::Objects giftType , Direction dir);
	virtual ~BaseGift() = 0 {};

	Resources::Objects getGiftType();

	virtual void update(sf::Time delta) override;
	virtual void fixCollision(const GameObj& other) override;

protected:


public:


protected:
	
	Resources::Objects m_giftType;

	float m_gravity = 5.f;
	float m_moveTime = 0.02f;
	float m_toatalTime = 0.0f;
};