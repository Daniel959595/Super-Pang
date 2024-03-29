#include "Resources.h"

#include "Direction.h"

#include <stdexcept>

namespace
{
    void setLeftPlayer(AnimationData::ListType& list)
    {
        for (auto& l : list) {
            l.left += 32;
            l.width *= -1;
        }
    }
    void setShot(AnimationData::ListType& list)
    {
        int i = 0;
        for (auto& l : list) {
            if (i++ % 3 == 0) {
                l.left += 10;
                l.width *= -1;
            }
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
        setLeftPlayer(palyer.m_data[Direction::Left]);
        
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
    AnimationData TriangleBallData() {
        auto ball = AnimationData{};

        const auto size = sf::Vector2i(112, 112);
        const auto initSpace = sf::Vector2i(0, 0);

        ball.m_data[Direction::Right].emplace_back(initSpace, size);
        ball.m_data[Direction::Left] = ball.m_data[Direction::Right];
        ball.m_data[Direction::Up] = ball.m_data[Direction::Right];
        ball.m_data[Direction::Down] = ball.m_data[Direction::Right];

        return ball;
    }
    AnimationData RegularShotData() {
        auto shot = AnimationData{};

        auto heightGap = 4;
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
        setShot(shot.m_data[Direction::Up]);

        return shot;  
                        
    }
    AnimationData BreakableTileData() {
        auto tile = AnimationData{};

        auto size = sf::Vector2i(34, 9);
        const auto step = sf::Vector2i(40, 0);
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
    AnimationData ScoreGiftData() {
        auto gift = AnimationData{};

        auto size = sf::Vector2i(66, 66);
        const auto step = sf::Vector2i(72, 0);
        const auto initSpace = sf::Vector2i(22, 69);

        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += step;
            return currentStart;
        };

        gift.m_data[Direction::Stay].emplace_back(currentStart, size);

        for (int i = 0; i < 10; i++)
            gift.m_data[Direction::Stay].emplace_back(nextStart(), size);

        return gift;
    }
    AnimationData LifeGiftData() {
        auto gift = AnimationData{};

        auto size = sf::Vector2i(20, 20);
        const auto initSpace = sf::Vector2i(160, 0);

        auto currentStart = initSpace;

        gift.m_data[Direction::Stay].emplace_back(currentStart, size);

        return gift;
    }
    AnimationData ShotGiftData() {
        auto gift = AnimationData{};

        auto size = sf::Vector2i(20, 20);
        const auto initSpace = sf::Vector2i(0, 0);

        auto currentStart = initSpace;

        gift.m_data[Direction::Stay].emplace_back(currentStart, size);

        return gift;
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

const sf::Font& Resources::getFont()
{
    if (m_font.getInfo().family.empty())
        m_font.loadFromFile("Neon.otf");
    return m_font;
    
}

Resources::Resources()
    : m_textures(Max), m_data(Max)
{
    loadTextures();

    m_data[Player]        = PlayerData();
    m_data[RegularBall]   = RegularBallData();
    m_data[TriangleBall]  = TriangleBallData();
    m_data[RegularShot]   = RegularShotData();
    m_data[BreakableTile] = BreakableTileData();
    m_data[ScoreGift]     = ScoreGiftData();
    m_data[LifeGift]      = LifeGiftData();
    m_data[ShotGift]      = ShotGiftData();
    //m_data[Backgrounds] = BackgroundsData();
}

void Resources::loadTextures()
{
    if (!m_textures[Player].loadFromFile("player.png"))
        throw std::runtime_error("Can't load file (player.png).");

    if (!m_textures[RegularBall].loadFromFile("Ball.png"))
        throw std::runtime_error("Can't load file (Ball.png).");
    m_textures[RegularBall].setSmooth(true);

    if (!m_textures[TriangleBall].loadFromFile("Ball.png"))
        throw std::runtime_error("Can't load file (TriangleBall.png).");

    if (!m_textures[Backgrounds].loadFromFile("Backgrounds.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");

    if (!m_textures[RegularShot].loadFromFile("Shot2.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");
    m_textures[RegularShot].setSmooth(true);

    if (!m_textures[BreakableTile].loadFromFile("Shot2.png"))
        throw std::runtime_error("Can't load file (Backgrounds.png).");
    m_textures[BreakableTile].setSmooth(true);

    if (!m_textures[ScoreGift].loadFromFile("Coins.png"))
        throw std::runtime_error("Can't load file (Coins.png).");
    m_textures[ScoreGift].setSmooth(true);

    if (!m_textures[LifeGift].loadFromFile("Gifts.png"))
        throw std::runtime_error("Can't load file (Coins.png).");
    m_textures[LifeGift].setSmooth(true);

    if (!m_textures[ShotGift].loadFromFile("Gifts.png"))
        throw std::runtime_error("Can't load file (Coins.png).");
    m_textures[ShotGift].setSmooth(true);
}
