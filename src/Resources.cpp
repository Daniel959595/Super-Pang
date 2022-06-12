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
        const auto step = sf::Vector2i(34, 0);

        auto palyer = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += step;
            return currentStart;
        };

        palyer.m_data[Direction::Right].emplace_back(currentStart, size);
        for (int i = 0; i < 4; i++) {
            palyer.m_data[Direction::Right].emplace_back(nextStart(), size);
        }
        
        palyer.m_data[Direction::Left] = palyer.m_data[Direction::Right];
        setLeft(palyer.m_data[Direction::Left]);
        
        currentStart = sf::Vector2i(10, 112);
        palyer.m_data[Direction::Stay].emplace_back(currentStart, size);
        palyer.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return palyer;
    }
    AnimationData RegularBallData() {
        auto ball = AnimationData{};

        const auto size = sf::Vector2i(112, 112);
        const auto initSpace = sf::Vector2i(0, 0);

        ball.m_data[Direction::Right].emplace_back(initSpace, size);
        ball.m_data[Direction::Left] = ball.m_data[Direction::Right];
        ball.m_data[Direction::Up]   = ball.m_data[Direction::Right];
        ball.m_data[Direction::Down] = ball.m_data[Direction::Right];

        return ball;
    }
    AnimationData RegularShotData() {
        auto shot = AnimationData{};

        auto heightGap = 2;
        auto size = sf::Vector2i(10, 32); 

        const auto initSpace = sf::Vector2i(398, 1566); 

        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            size.y += heightGap;
            return currentStart;
        };

        shot.m_data[Direction::Up].emplace_back(currentStart, size);

        for (int i = 1; i < 80; i++)
            shot.m_data[Direction::Up].emplace_back(nextStart(), size);

        return shot;  
                        
    }
    AnimationData BreakableTileData() {
        auto tile = AnimationData{};

        auto size = sf::Vector2i(34, 9);
        const auto step = sf::Vector2i(6, 0);
        const auto initSpace = sf::Vector2i(7, 618);

        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += step;
            return currentStart;
        };

        tile.m_data[Direction::Stay].emplace_back(currentStart, size);

        for (int i = 0; i < 4; i++)
            tile.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return tile;
    }


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

    m_data[Player]        = PlayerData();
    m_data[RegularBall]   = RegularBallData();
    m_data[RegularShot]   = RegularShotData();
    m_data[BreakableTile] = BreakableTileData();
    //m_data[Backgrounds] = BackgroundsData();
}

void Resources::loadTextures()
{
    if (!m_textures[Player].loadFromFile("player.png"))
        throw std::runtime_error("Can't load file (player.png).");
    if (!m_textures[RegularBall].loadFromFile("Ball.png"))
        throw std::runtime_error("Can't load file (Ball.png).");
    m_textures[RegularBall].setSmooth(true);
    if (!m_textures[Backgrounds].loadFromFile("Backgrounds.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");

    if (!m_textures[RegularShot].loadFromFile("Shot2.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");
    m_textures[RegularShot].setSmooth(true);

    if (!m_textures[BreakableTile].loadFromFile("Shot2.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");
    m_textures[BreakableTile].setSmooth(true);
}
