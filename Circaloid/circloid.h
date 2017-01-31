#ifndef CIRCLOID_H
#define CIRCLOID_H

#include <cassert>

#include "SFML/Graphics.hpp"

class Circloid
{
    const sf::Vector2f m_windims;

    sf::Vector2f m_speed;

    sf::CircleShape m_circle;

    const int m_div;

    const float m_frame;

    const float m_subframe;

public:

    Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed,
             const float radius, const sf::Color &color, const int div, const float frame);

    void move();

    void check_border();

    void display(sf::RenderWindow &window);

};

float squr(const float scalar);

float vectralize(const sf::Vector2f &vectol);

#endif // CIRCLOID_H
