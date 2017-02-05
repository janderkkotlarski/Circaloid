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

    const float m_light;
    float m_relative;

    const float m_accel;

    const float m_pheta;

    float m_quinergy;

    const float m_questore;
    const float m_quove;

    sf::CircleShape m_circle;
    sf::CircleShape m_mircle;

    sf::CircleShape m_bircle;

    const int m_div;

    const float m_frame;

    const float m_subframe;

    const std::vector <sf::Keyboard::Key> m_keys;

    std::vector <bool> m_keypressed;

    void relativate();
    void accelerate();

    void ceiling();

    void rotate();

    void scale_radius();

    void quinergy_restore();

    void check_border();


public:

    Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
             const float accel, const float pheta, const float radius, const int points, const sf::Color &color,
             const int div, const float frame, const std::vector<sf::Keyboard::Key> &keys);

    void check_keys();

    void move();

    void display(sf::RenderWindow &window);

};

void set_circle(const float radius, const sf::Vector2f &posit, const int points,
                const sf::Color &color, sf::CircleShape &circle);

float squr(const float scalar);

float vectralize(const sf::Vector2f &vectol);

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed);

#endif // CIRCLOID_H
