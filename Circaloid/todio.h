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
    std::vector <bool> m_loops;
    std::vector <sf::SoundBuffer> m_buffers;
    std::vector <sf::Sound> m_sounds;

public:

    Todio(const std::vector <std::string>& names,
          const std::vector<bool> &loops);

    void ring(const int here);

    void stop(const int here);
};

#endif // TODIO_H
