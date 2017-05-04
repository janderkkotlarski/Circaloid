#ifndef SEEKER_H
#define SEEKER_H

#include <cassert>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "functions.h"

class Seeker
{
    sf::Vector2f m_speed;
    float m_accel;

    float m_frame;

    int m_self;
    int m_target;

    sf::CircleShape m_circle;

    void set_circle(const float radius,
                    const sf::Vector2f& posit);

public:

    explicit Seeker(const float boundary,
                    const sf::Vector2f& posit,
                    const sf::Vector2f& speed,
                    const float frame,
                    const int self,
                    const int target);

    ~Seeker();

    sf::Vector2f get_posit() const noexcept
    { return m_circle.getPosition(); }
    float get_radius() const noexcept
    { return m_circle.getRadius(); }

    int get_self() const noexcept
    { return m_self; }
    int get_target() const noexcept
    { return m_target; }

    void jump(const sf::Vector2f& leap) noexcept
    { m_circle.move(leap); }

    void set_speed(const sf::Vector2f& target_posit);

    void move() noexcept
    { m_circle.move(m_frame*m_speed); }

    void display(sf::RenderWindow& window)
    { window.draw(m_circle); }
};

#endif // SEEKER_H
