#ifndef TODIO_H
#define TODIO_H

#include <cassert>
#include <string>
#include <vector>

#include "SFML/Audio.hpp"

class Todio
{
    std::vector <std::string> m_names;
    std::vector <sf::SoundBuffer> m_buffers;
    std::vector <sf::Sound> m_sounds;

public:

    Todio();
};

#endif // TODIO_H
