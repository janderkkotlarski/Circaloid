#ifndef TOPHICS_H
#define TOPHICS_H

#include <cassert>

#include "SFML/Graphics.hpp"
#include "functions.h"

class Tophics
{
    // const float m_frame;

    // const float m_subframe;

    const float m_boundary;

    sf::Texture m_texture;

    sf::Sprite m_sprite;
    sf::Sprite m_smite;

    sf::Texture m_dexture;

    sf::Sprite m_direct;
    sf::Sprite m_disect;

public:

    explicit Tophics(const std::string &name, const sf::Vector2f &posit,
                     const float boundary, const float rotation);

    ~Tophics();

    sf::Vector2f get_posit() const noexcept
    { return m_sprite.getPosition();}
    sf::Vector2f get_mosit() const noexcept
    { return m_smite.getPosition(); }

    float get_radius() noexcept
    { return sprite_radius(m_sprite );}
    float get_madius() noexcept
    { return sprite_radius(m_smite); }

    float get_rotate() const noexcept
    { return m_sprite.getRotation(); }

    void rotate(const float rotation);

    void move_sprite(const sf::Vector2f &delta_posit);

    void check_border(const sf::Vector2f &speed);

    void move_smite(const sf::Vector2f &speed);

    void set_scale(const float scale);

    void display(sf::RenderWindow &window);
};

#endif // TOPHICS_H
