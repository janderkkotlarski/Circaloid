#ifndef TODIO_H
#define TODIO_H

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "SFML/Audio.hpp"

class Todio
{
    std::vector <std::string> m_names;
    std::vector <sf::SoundBuffer> m_buffers;
    sf::Sound m_sounds;

public:

    Todio(std::vector <std::string>& names);

    void ring();

    void stop();
};

#endif // TODIO_H
