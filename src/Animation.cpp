#include "Animation.h"

#include "Utilities.h"

//const auto AnimationTime = sf::seconds(0.1f);

Animation::Animation(const AnimationData& data, Resources::Objects object, Direction dir, sf::Sprite& sprite, sf::Time time)
    : m_data(data), m_dir(dir), m_sprite(sprite), m_animationTime(time)
{
    m_sprite.setTexture(Resources::instance().texture(object));
    scaleSprite(object);
    update();
}

void Animation::scaleSprite(Resources::Objects object)
{
    switch (object)
    {
    case Resources::Objects::Player: m_sprite.setScale(4, 4); break;
    case Resources::Objects::RegularShot:   m_sprite.setScale(TABLE_HEIGHT / 191.f, TABLE_HEIGHT / 191.f); break;

    default:
        break;
    }
}

void Animation::direction(Direction dir)
{
    //if (m_dir == dir || dir == Direction::Stay)
    if (m_dir == dir)
    {
        return;
    }

    m_dir = dir;
    m_index = 0;
    update();
}

void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= m_animationTime)
    {
        m_elapsed -= m_animationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}
