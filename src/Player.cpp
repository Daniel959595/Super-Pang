#include "Player.h"

#include <optional>

constexpr auto PlayerSpeed = 250.f;


Player::Player()
    : MoveAble(Resources::Objects::Player, Direction::Stay)
{
    float x = (WINDOW_WIDTH / 2) - (m_sprite.getGlobalBounds().width / 2);
    float y = BACBGROUND_HEIGHT  -  m_sprite.getGlobalBounds().height - FRAME_WIDTH;
    
    m_sprite.setPosition(sf::Vector2f(x,y));
}

void Player::dirFromKey()
{
    static const
        std::initializer_list<std::pair<sf::Keyboard::Key, Direction>>
        keyToVectorMapping =
    {
        { sf::Keyboard::Right, Direction::Right },
        { sf::Keyboard::Left,  Direction::Left  },
        { sf::Keyboard::Up   , Direction::Up    },
        { sf::Keyboard::Down , Direction::Down  },
        { sf::Keyboard::Space, Direction::Stay  },
    };

    for (const auto& pair : keyToVectorMapping)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            direction(pair.second);
            return;
        }
    }
    m_dir = Direction::Stay;
    //m_faceRight = true;
    m_animation.direction(m_dir);
}

void Player::direction(Direction dir)
{
    m_dir = dir;
    m_animation.direction(dir);
    if (dir == Direction::Left)
        m_faceRight = false;
    else
        m_faceRight = true;
}

void Player::update(sf::Time delta)
{
    dirFromKey();
    if (m_dir == Direction::Stay)
    {
        return;
    }

    m_sprite.move(toVector(m_dir) * delta.asSeconds() * PlayerSpeed);
    m_animation.update(delta);
}


