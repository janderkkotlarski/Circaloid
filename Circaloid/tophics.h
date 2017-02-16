#ifndef TOPHICS_H
#define TOPHICS_H

#include <cassert>

#include "SFML/Graphics.hpp"
#include "functions.h"

class Tophics
{
    // const float m_frame;

    // const float m_subframe;



    sf::Texture m_texture;

    sf::Sprite m_sprite;
    sf::Sprite m_smite;

    sf::Texture m_dexture;

    sf::Sprite m_direct;
    sf::Sprite m_disect;

public:

    explicit Tophics(const std::string &name, const sf::Vector2f &posit, const float rotation);

    ~Tophics();

};

#endif // TOPHICS_H
