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
        Ball,
        Backgrounds,
        Max,
    };

    static Resources& instance();

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    //const sf::Texture& texture() const { return m_texture; }
    const sf::Texture& texture(Objects object) const;
    const AnimationData& animationData(Objects object) { return m_data[object]; }

private:
    Resources();
    void loadTextures();
public:

private:

    //sf::Texture m_texture;
    std::vector<sf::Texture> m_textures;
    std::vector<AnimationData> m_data;
};
