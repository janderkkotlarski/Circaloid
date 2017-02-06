#ifndef TOHOID_H
#define TOHOID_H

#include <iostream>
#include <cassert>
#include <cmath>

#include "SFML/Graphics.hpp"

#include "bullet.h"

class Tohoid
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

    sf::Texture m_texture;

    sf::Sprite m_sprite;
    sf::Sprite m_smite;

    const int m_div;

    const float m_frame;

    const float m_subframe;

    const std::vector <sf::Keyboard::Key> m_keys;

    std::vector <bool> m_keypressed;

    std::vector <Bullet> m_bullets;
    bool m_bullet_shot;

    bool m_alive;



    void relativate();
    void accelerate();
    void ceiling();

    void rotate();

    void scale_radius();

    void quinergy_restore();

    void check_keys();

    void check_border();

    void bullet_shoot();
    void move_bullets();
    void check_bullet_border();
    void bullets_hurt(std::vector <Tohoid> &touhous);

    void display_bullets(sf::RenderWindow &window);


public:

    Tohoid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
             const float accel, const float pheta, const std::__cxx11::string &image_name, const int div,
             const float frame, const std::vector<sf::Keyboard::Key> &keys);    

    ~Tohoid();

    sf::Vector2f get_posit() const noexcept {return m_sprite.getPosition();}
    float get_radius() const noexcept {return 0.25f*(m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height);}
    float get_quinergy() const noexcept {return m_quinergy;}
    bool get_vivid() const noexcept {return m_alive;}

    void dies() noexcept {m_alive = false;}

    void qi_damage(const float qi_hurt) noexcept {m_quinergy += qi_hurt;}

    void move(std::vector <Tohoid> &touhous);

    void display(sf::RenderWindow &window);

};

sf::Vector2f rotation2direction(const float rotation);

void set_sprite(const sf::Vector2f &posit, sf::Sprite &sprite);

float squr(const float scalar) noexcept;

float vectralize(const sf::Vector2f &vectol) noexcept;

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed);

#endif // TOHOID_H
