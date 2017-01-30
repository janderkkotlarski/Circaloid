#ifndef CIRCLOID_H
#define CIRCLOID_H

#include <cassert>

#include "SFML/Graphics.hpp"

class Circloid
{
    sf::CircleShape m_circle;

    sf::Vector2f m_speed;

    const int m_div;

    const float m_frame;

};

#endif // CIRCLOID_H
