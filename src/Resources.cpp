#include "Resources.h"

#include "Direction.h"

#include <stdexcept>

namespace
{
    void setLeft(AnimationData::ListType& list)
    {
        for (auto& i : list) {
            i.left += 32;
            i.width *= -1;
        }
    }
    AnimationData PlayerData()
    {
        const auto size = sf::Vector2i(32, 32);
        const auto initSpace = sf::Vector2i(10, 2);
        const auto textureWidth = sf::Vector2i(34, 0);

        auto palyer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += textureWidth;
            return currentStart;
        };

        palyer.m_data[Direction::Right].emplace_back(currentStart, size);
        palyer.m_data[Direction::Right].emplace_back(nextStart(), size);
        palyer.m_data[Direction::Right].emplace_back(nextStart(), size);
        palyer.m_data[Direction::Right].emplace_back(nextStart(), size);
        palyer.m_data[Direction::Right].emplace_back(nextStart(), size);
        
        palyer.m_data[Direction::Left] = palyer.m_data[Direction::Right];
        setLeft(palyer.m_data[Direction::Left]);
        
        currentStart = sf::Vector2i(10, 112);
        palyer.m_data[Direction::Stay].emplace_back(currentStart, size);
        palyer.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return palyer;
    }
    /*AnimationData BackgroundsData() {

    }*/

}


Resources& Resources::instance()
{
    static Resources instance;
    return instance;
}

const sf::Texture& Resources::texture(Objects object) const
{
    return m_textures[object];
}

Resources::Resources()
    : m_textures(Max), m_data(Max)
{
    loadTextures();

    m_data[Player] = PlayerData();
    //m_data[Ball] = BallData();
    //m_data[Backgrounds] = BackgroundsData();
}

void Resources::loadTextures()
{
    if (!m_textures[Player].loadFromFile("player.png"))
        throw std::runtime_error("Can't load file (player.png).");
    if (!m_textures[Backgrounds].loadFromFile("Backgrounds.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");
}
