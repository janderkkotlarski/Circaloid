#ifndef SEEKER_H
#define SEEKER_H

#include <cassert>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "functions.h"

class Seeker
{
    float m_boundary;

    sf::Vector2f m_speed;

    float m_accel;

    float m_subframe;

    int m_target;

    sf::CircleShape m_circle;

    void set_circle(const float radius, const sf::Vector2f &posit);

public:

    Seeker(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit,
           const sf::Vector2f &speed, const float &light, const float subframe,
           const int target, const int self);

    ~Seeker();

    sf::Vector2f get_posit() const noexcept {return m_circle.getPosition();}
    float get_radius() const noexcept {return m_circle.getRadius();}

    void jump(const sf::Vector2f &leap) noexcept {m_circle.move(leap);}

    void set_speed();
    void move() noexcept {m_circle.move(m_subframe*m_speed);}

    void display(sf::RenderWindow &window) {window.draw(m_circle);}

};

#endif // SEEKER_H