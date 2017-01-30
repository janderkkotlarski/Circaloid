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

public:

    Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed,
             const float radius, const sf::Color &color, const int div, const float frame);

    void move();

    void display(sf::RenderWindow &window);

};

#endif // CIRCLOID_H
