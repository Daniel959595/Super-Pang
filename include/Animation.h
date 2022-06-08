#pragma once

#include <SFML/Graphics.hpp>

#include "Utilities.h"
#include "AnimationData.h"

class Animation
{
public:
    //Animation(const AnimationData& data, Resources::Objects object, Direction dir, sf::Sprite& sprite);
    Animation(const AnimationData& data, Resources::Objects object, Direction dir, sf::Sprite& sprite, sf::Time time);

    void direction(Direction dir);
    void update(sf::Time delta);

private:
    void scaleSprite(Resources::Objects object);
    void update();
    const AnimationData& m_data;

private:

    sf::Time m_animationTime;
    sf::Time m_elapsed = {};
    Direction m_dir;
    int m_index = 0;
    sf::Sprite& m_sprite;
};