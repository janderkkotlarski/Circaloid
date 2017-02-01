#ifndef CIRCLOID_H
#define CIRCLOID_H

#include <iostream>
#include <cassert>
#include <cmath>

#include "SFML/Graphics.hpp"

class Circloid
{
    const sf::Vector2f m_windims;

    const float m_boundary;

    sf::Vector2f m_speed;

    sf::CircleShape m_circle;

    sf::CircleShape m_mircle;

    sf::CircleShape m_bircle;

    const int m_div;

    const float m_frame;

    const float m_subframe;

    void check_border();

public:

    Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed,
             const float radius, const sf::Color &color, const int div, const float frame);

    void move();

    void display(sf::RenderWindow &window);

};

void set_circle(const float radius, const sf::Vector2f &posit, const sf::Color &color,
                sf::CircleShape &circle);

float squr(const float scalar);

float vectralize(const sf::Vector2f &vectol);

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit);

#endif // CIRCLOID_H
