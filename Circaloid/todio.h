#ifndef TODIO_H
#define TODIO_H

#include <cassert>
#include <string>
#include <vector>
#include <iostream>

#include "SFML/Audio.hpp"

#include "functions.h"

class Todio
{
    std::string m_folder_name;
    std::string m_filename;
    bool m_loops;
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;

public:

    Todio(const std::string& foldername,
          const std::string& filename,
          const bool loops);

    void rebuff();

    void ring();

    void stop();
};

#endif // TODIO_H
