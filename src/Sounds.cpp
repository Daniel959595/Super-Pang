#include "Sounds.h"

#include <stdexcept>




Sounds& Sounds::instance()
{
    static Sounds instance;
    return instance;
}

//sf::SoundBuffer& Sounds::getSoundBuffer(Sound soundType)
//{
//    switch (soundType)
//    {
//    case Sounds::Steps:          return m_buffers[Steps];         break;
//    case Sounds::BallExplosion:  return m_buffers[BallExplosion]; break;
//    case Sounds::RegularShot:    return m_buffers[RegularShot];   break;
//    case Sounds::TileBreaking:   return m_buffers[TileBreaking];  break;
//    case Sounds::Gift:           return m_buffers[Gift];          break;
//    case Sounds::Faild:          return m_buffers[Faild];         break;
//    case Sounds::GameOver:       return m_buffers[GameOver];      break;
//    case Sounds::Succeed:        return m_buffers[Succeed];       break;
//    default:
//        break;
//    }
//}

void Sounds::activateSound(Sound soundType)
{
    m_sounds[soundType].play();
}

Sounds::Sounds()
    : m_buffers(Max), m_sounds(Max)
{
    loadBuffers();
    setVolume();
    LoadSounds();

}

void Sounds::loadBuffers()
{
    //m_buffers[Steps].loadFromFile("StepsSound.wav");
    m_buffers[BallExplosion].   loadFromFile("BallonSound.wav");
    m_buffers[RegularShot].     loadFromFile("ShotSound.wav");
    m_buffers[TileBreaking].    loadFromFile("TileBreaking.wav");
    //m_buffers[Gift].            loadFromFile();
    m_buffers[Faild].           loadFromFile("Faild.ogg");
    //m_buffers[GameOver].        loadFromFile();
    //m_buffers[Succeed].         loadFromFile();
}

void Sounds::LoadSounds()
{
    m_sounds[Steps].setBuffer(m_buffers[Steps]);
    m_sounds[BallExplosion].setBuffer(m_buffers[BallExplosion]);
    m_sounds[RegularShot].setBuffer(m_buffers[RegularShot]);
    m_sounds[TileBreaking].setBuffer(m_buffers[TileBreaking]);
    m_sounds[Gift].setBuffer(m_buffers[Gift]);
    m_sounds[Faild].setBuffer(m_buffers[Faild]);
    m_sounds[GameOver].setBuffer(m_buffers[GameOver]);
    m_sounds[Succeed].setBuffer(m_buffers[Succeed]);
    m_sounds[Faild].setBuffer(m_buffers[Faild]);
}

void Sounds::setVolume()
{
    for (auto& s : m_sounds) {
        s.setVolume(VOLUME);
    }
}
