#ifndef BULLET_H
#define BULLET_H

#include <cassert>

#include "SFML/Graphics.hpp"

class Bullet
{
    float m_boundary;

    float m_veloc;

    sf::Vector2f m_direction;

    float m_subframe;

    sf::CircleShape m_circle;

public:

    Bullet(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit, const float veloc,
           const sf::Vector2f &direction, const float subframe);

    ~Bullet();

    void set_circle(const float radius, const sf::Vector2f &posit);

    void set_veloc(const float veloc) noexcept {m_veloc = veloc;}
    void set_direction(const sf::Vector2f &direction) noexcept {m_direction = direction;}

    sf::Vector2f get_posit() const noexcept {return m_circle.getPosition();}
    float get_radius() const noexcept {return m_circle.getRadius();}

    void jump(const sf::Vector2f &leap) noexcept{m_circle.move(leap);}
    void move() noexcept{m_circle.move(m_subframe*m_veloc*m_direction);}

    void display(sf::RenderWindow &window) {window.draw(m_circle);}
};

#endif // BULLET_H
