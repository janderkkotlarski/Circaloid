#ifndef TOHOID_H
#define TOHOID_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>

#include "SFML/Graphics.hpp"


#include "functions.h"
#include "tophics.h"
#include "bullet.h"
#include "seeker.h"

class Tohoid
{
    const float m_boundary;

    sf::Vector2f m_speed;
    const float m_light;

    float m_relative;
    const float m_accel;

    const float m_pheta;

    float m_quinergy;
    const float m_questore;

    Tophics m_tophics;

    const float m_frame;

    const std::vector <sf::Keyboard::Key> m_keys;

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

    void scale_radius()
    { m_tophics.set_scale(m_quinergy); }

    void quinergy_restore();

    void bullet_shoot();
    void danmaku_shoot();
    void seeker_shoot(std::vector <Tohoid> &touhous);

    void move_bullets(std::vector<Tohoid> &touhous);
    void check_bullet_border();
    void check_seeker_border();

    void bullets_hurt(std::vector <Tohoid> &touhous,
                      std::vector<Bullet> &bullets);

    void seeker_hurt(std::vector <Tohoid> &touhous,
                     std::vector <Seeker> &seeker);

    void move_tophics();

    void display_bullets(sf::RenderWindow &window);

public:

    explicit Tohoid(const sf::Vector2f &windims, const sf::Vector2f &posit,
                    const float rotation, const std::string &image_name, const float frame,
                    const std::vector <sf::Keyboard::Key> &keys);

    ~Tohoid();

    sf::Vector2f get_posit() const noexcept
    { return m_tophics.get_posit(); }
    sf::Vector2f get_mosit() const noexcept
    { return m_tophics.get_mosit(); }

    float get_radius() noexcept
    { return m_tophics.get_radius(); }
    float get_madius() noexcept
    { return m_tophics.get_madius(); }

    float get_rotate() const noexcept
    { return m_tophics.get_rotate(); }

    float get_quinergy() const noexcept
    { return m_quinergy; }
    bool get_vivid() const noexcept
    { return m_alive; }

    void reimage();

    void dies() noexcept
    { m_alive = false; }

    void qi_damage(const float qi_hurt) noexcept
    { m_quinergy += qi_hurt; }

    void move(std::vector <Tohoid> &touhous);

    void display(sf::RenderWindow &window);

    int touhou_self(std::vector <Tohoid> &touhous);
    int touhou_target(std::vector <Tohoid> &touhous);

};

std::vector <sf::Vector2f> touhous2posits(std::vector <Tohoid> &touhous);

std::vector <bool> touhous2alives(std::vector <Tohoid> &touhous);

void bullets_hit(Tohoid &touhou,
                 std::vector<Bullet> &bullets,
                 const float qi_hurt,
                 const float scale,
                 const float boundary);

void seeker_hit(Tohoid &touhou,
                std::vector <Seeker> &seeker,
                const float qi_hurt,
                const float scale,
                const float boundary);

#endif // TOHOID_H
