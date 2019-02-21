#ifndef TODIO_H
#define TODIO_H

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "SFML/Audio.hpp"

class Todio
{
    std::string m_name;
    bool m_loops;
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;

public:

    Todio(const std::string& name,
          const bool loops);

    void ring();

    void stop();
};

#endif // TODIO_H
