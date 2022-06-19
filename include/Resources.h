#pragma once

#include "AnimationData.h"

#include <SFML/graphics.hpp>

#include <vector>

class Resources
{
public:
    enum Objects
    {
        Player,
        RegularBall,
        TriangleBall,
        Backgrounds,
        RegularShot,
        DoubleShot, // same as regular. 
        BreakableTile,
        UnbreakableTile,
        ScoreGift,
        ShotsGift,
        ExtraLifeGift,
        Max,
    };

    static Resources& instance();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    const sf::Texture& texture(Objects object) const;
    const AnimationData& animationData(Objects object) { return m_data[object]; }

    const sf::Font& getFont();

private:
    Resources();
    void loadTextures();

public:

private:

    sf::Font m_font;

    std::vector<sf::Texture> m_textures;
    std::vector<AnimationData> m_data;
};
