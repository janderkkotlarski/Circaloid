#ifndef BULLET_H
#define BULLET_H

#include <cassert>

#include "SFML/Graphics.hpp"

class Bullet
{
    const float m_boundary;

    float m_veloc;

    sf::Vector2f m_direction;

    const float m_subframe;

    sf::CircleShape m_circle;

public:

    Bullet(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit, const float veloc,
           const sf::Vector2f &direction, const float subframe, const sf::Color &color);

    void set_circle(const float radius, const sf::Vector2f &posit, const sf::Color &color);
};

#endif // BULLET_H
