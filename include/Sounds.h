#pragma once

#include <SFML/graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Utilities.h"

class Sounds
{
public:
    enum Sound
    {
        Steps,
        BallExplosion,
        RegularShot,
        TileBreaking,
        Gift,
        Faild,
        GameOver,
        Succeed,
        Max,
    };

    static Sounds& instance();

    Sounds(const Sounds&) = delete;
    Sounds& operator=(const Sounds&) = delete;

    //sf::SoundBuffer& getSoundBuffer(Sound soundType);
    void activateSound(Sound soundType);

private:
    Sounds();
    void loadBuffers();
    void LoadSounds();
    void setVolume();

public:

private:
    std::vector<sf::Sound> m_sounds;
    std::vector<sf::SoundBuffer> m_buffers;
};
