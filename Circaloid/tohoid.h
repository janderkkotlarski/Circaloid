#ifndef TOHOID_H
#define TOHOID_H

#include <iostream>
#include <cassert>
#include <cmath>

#include "SFML/Graphics.hpp"


#include "functions.h"
#include "tophics.h"
#include "bullet.h"
#include "seeker.h"

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

    sf::Texture m_dexture;

    sf::Sprite m_direct;
    sf::Sprite m_disect;

    Tophics m_tophics;

    const int m_div;

    const float m_frame;

    const float m_subframe;

    const std::vector <sf::Keyboard::Key> m_keys;

    std::vector <bool> m_keypressed;

    std::vector <Bullet> m_bullets;

    std::vector <Seeker> m_seeker;

    bool m_bullet_shot;
    bool m_danmaku_shot;
    bool m_seeker_shot;

    bool m_alive;

    ///////////////////////////////////////////////////////////////////////////

    void relativate();
    void accelerate();
    void ceiling();

    void rotate();

    void scale_radius();

    void quinergy_restore();

    void check_keys();

    void check_border();

    void bullet_shoot();
    void danmaku_shoot();
    void seeker_shoot(std::vector <Tohoid> &touhous);

    void move_bullets(const std::vector<bool> &alives, const std::vector<sf::Vector2f> &posits);
    void check_bullet_border();
    void check_seeker_border();
    void bullets_hurt(std::vector <Tohoid> &touhous);
    void seeker_hurt(std::vector <Tohoid> &touhous);

    void display_bullets(sf::RenderWindow &window);

public:

    explicit Tohoid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
             const float accel, const float rotation, const float pheta, const std::string &image_name, const int div,
             const float frame, const std::vector<sf::Keyboard::Key> &keys);    

    ~Tohoid();

    sf::Vector2f get_posit() const noexcept {return m_sprite.getPosition();}
    sf::Vector2f get_mosit() const noexcept {return m_smite.getPosition();}
    float get_radius() const noexcept {return 0.25f*(m_sprite.getGlobalBounds().width + m_sprite.getGlobalBounds().height);}
    float get_madius() const noexcept {return 0.25f*(m_smite.getGlobalBounds().width + m_smite.getGlobalBounds().height);}
    float get_rotate() const noexcept {return m_sprite.getRotation();}

    float get_quinergy() const noexcept {return m_quinergy;}
    bool get_vivid() const noexcept {return m_alive;}

    void dies() noexcept {m_alive = false;}

    void qi_damage(const float qi_hurt) noexcept {m_quinergy += qi_hurt;}

    void move(std::vector <Tohoid> &touhous);

    void display(sf::RenderWindow &window);

    int touhou_self(std::vector <Tohoid> &touhous);
    int touhou_target(std::vector <Tohoid> &touhous);

};

std::vector <sf::Vector2f> touhous2posits(std::vector <Tohoid> &touhous);

std::vector <bool> touhous2alives(std::vector <Tohoid> &touhous);


#endif // TOHOID_H
