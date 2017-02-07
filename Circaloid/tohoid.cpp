#include "tohoid.h"

Tohoid::Tohoid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
                   const float accel, const float rotation, const float pheta, const std::string &image_name,
                   const int div, const float frame, const std::vector <sf::Keyboard::Key> &keys)
    : m_windims(windims), m_boundary(0.5f*windims.x), m_speed(speed), m_light(squr(light)), m_relative(1.0f),
      m_accel(accel), m_pheta(pheta), m_quinergy(1.0f), m_questore(0.02f), m_quove(-0.02f), m_texture(), m_sprite(), m_smite(),
      m_div(div), m_frame(frame), m_subframe(frame/static_cast<float>(div)),
      m_keys(keys), m_keypressed(), m_bullets(), m_bullet_shot(false), m_danmaku_shot(false), m_alive(true)
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);
    assert(posit.x >= -windims.x);
    assert(posit.y >= -windims.y);
    assert(posit.x <= windims.x);
    assert(posit.y <= windims.y);

    assert(image_name != "");

    assert(m_div > 0);
    assert(m_frame > 0.0f);

    assert(m_keys.size() > 0);

    for (int count{0}; count < static_cast<int>(m_keys.size()); ++count)
    {
        m_keypressed.push_back(false);
    }

    assert(m_keys.size() == m_keypressed.size());

    if (!m_texture.loadFromFile(image_name))
    {
        std::cerr << image_name << "not found!\n";
    }

    m_texture.setSmooth(true);

    m_sprite.setTexture(m_texture);
    m_smite.setTexture(m_texture);

    set_sprite(posit, rotation, m_sprite);
    set_sprite(posit, rotation, m_smite);
}

Tohoid::~Tohoid()
{
}

void Tohoid::relativate()
{
    const float minim{0.25f};

    assert(minim > 0.0f);

    if (vectralize(m_speed) < squr(m_light))
    {
        m_relative = (1.0f - minim)*sqrt(1 - vectralize(m_speed)/squr(m_light)) + minim;
    }

    if (m_relative < minim)
    {
        m_relative = minim;
    }
}

void Tohoid::accelerate()
{
    if (m_keypressed[0] || m_keypressed[1])
    {
        const sf::Vector2f accer{m_relative*m_accel*rotation2direction(m_sprite.getRotation())};

        if (m_keypressed[0])
        {
            m_speed += accer;

            m_quinergy += m_subframe*m_quove;
        }

        if (m_keypressed[1])
        {
            m_speed -= accer;

            m_quinergy += m_subframe*m_quove;
        }
    }
}

void Tohoid::ceiling()
{
    if (vectralize(m_speed) > squr(m_light))
    {
        m_speed *= m_light/std::sqrt(vectralize(m_speed));
    }
}

void Tohoid::rotate()
{
    if (m_keypressed[2])
    {
        m_sprite.rotate(m_relative*m_pheta);
        m_smite.rotate(m_relative*m_pheta);

        m_quinergy += m_subframe*m_quove;
    }

    if (m_keypressed[3])
    {
        m_sprite.rotate(-m_relative*m_pheta);
        m_smite.rotate(-m_relative*m_pheta);

        m_quinergy += m_subframe*m_quove;
    }
}

void Tohoid::scale_radius()
{
    m_sprite.setScale(m_quinergy, m_quinergy);
    m_smite.setScale(m_quinergy, m_quinergy);
}

void Tohoid::quinergy_restore()
{
    m_quinergy += m_subframe*m_questore;

    if (m_quinergy > 1.0f)
    {
        m_quinergy = 1.0f;
    }
}

void Tohoid::check_keys()
{
    for (int count{0}; count < static_cast<int>(m_keys.size()); ++count)
    {
        if (sf::Keyboard::isKeyPressed(m_keys[count]))
        {
            m_keypressed[count] = true;
        }
        else
        {
            m_keypressed[count] = false;
        }
    }
}

void Tohoid::check_border()
{
    if (vectralize(m_sprite.getPosition()) > squr(m_boundary))
    {
        m_sprite.setPosition(mirrorize(m_boundary, m_sprite.getPosition(), m_speed));
    }
}

void Tohoid::bullet_shoot()
{
    if (m_keypressed[4])
    {
        if (!m_bullet_shot)
        {
            const float qi_loss{-0.01f};

            m_quinergy += qi_loss;

            m_bullets.push_back(Bullet(m_windims, m_boundary, m_sprite.getPosition(), m_light,
                                       rotation2direction(m_sprite.getRotation()), m_subframe, bullet_type::normal));

            const sf::Vector2f leap{(0.505f*m_sprite.getGlobalBounds().height + 1.01f*m_bullets.back().get_radius())*rotation2direction(m_sprite.getRotation())};

            m_bullets.back().jump(leap);

            m_bullet_shot = true;
        }
    }
    else
    {
        m_bullet_shot = false;
    }
}

void Tohoid::danmaku_shoot()
{
    if (m_keypressed[5])
    {
        if (!m_danmaku_shot)
        {
            const float qi_loss{-0.07f};
            assert(qi_loss < 0.0f);

            m_quinergy += qi_loss;

            const int number{8};
            assert(number > 1);

            const float delta_rotate{180.0f/static_cast<float>(number)};

            float rotate{(0.5f - static_cast<float>(number/2))*delta_rotate};

            for (int count{0}; count < number; ++count)
            {
                const float rotation{rotate + m_sprite.getRotation()};

                const sf::Vector2f direction{rotation2direction(rotation)};

                m_bullets.push_back(Bullet(m_windims, m_boundary, m_sprite.getPosition(), m_light,
                                           direction, m_subframe, bullet_type::danmaku));

                const sf::Vector2f leap{(0.505f*m_sprite.getGlobalBounds().height + 1.01f*m_bullets.back().get_radius())*direction};

                m_bullets.back().jump(leap);

                rotate += delta_rotate;
            }

            m_danmaku_shot = true;
        }
    }
    else
    {
        m_danmaku_shot = false;
    }
}

void Tohoid::move_bullets()
{
    for (int count{0}; count < static_cast<int>(m_bullets.size()); ++count)
    {
        m_bullets[count].bullet_speed(m_light);
        m_bullets[count].move();
    }
}

void Tohoid::check_bullet_border()
{
    if (m_bullets.size() > 0)
    {
        for (int count{0}; count < static_cast<int>(m_bullets.size()); ++count)
        {
            if (vectralize(m_bullets[count].get_posit()) > squr(m_boundary - m_bullets[count].get_radius()))
            {
                m_bullets[count] = m_bullets.back();

                m_bullets.pop_back();

                --count;
            }
        }
    }
}

void Tohoid::bullets_hurt(std::vector <Tohoid> &touhous)
{
    if ((m_bullets.size() > 0) && (touhous.size() > 0))
    {
        const float qi_hurt{-0.05f};

        for (int iter{0}; iter < static_cast<int>(touhous.size()); ++iter)
        {
            if (touhous[iter].get_vivid())
            {
                for (int count{0}; count < static_cast<int>(m_bullets.size()); ++count)
                {
                    const float dist_2{vectralize(m_bullets[count].get_posit() - touhous[iter].get_posit())};

                    const float mist_2{vectralize(m_bullets[count].get_posit() - touhous[iter].get_mosit())};

                    const float radi_2{squr(m_bullets[count].get_radius() + touhous[iter].get_radius())};

                    const float madi_2{squr(m_bullets[count].get_radius() + touhous[iter].get_madius())};

                    const float bound_2{squr(m_boundary + touhous[iter].get_madius())};

                    const float mosit_2{vectralize(touhous[iter].get_mosit())};

                    if ((dist_2 <= radi_2) ||
                        ((mist_2 <= madi_2) && (mosit_2 <= bound_2)))
                    {
                        m_bullets[count] = m_bullets.back();

                        m_bullets.pop_back();

                        touhous[iter].qi_damage(qi_hurt);

                        --count;
                    }
                }
            }
        }
    }
}

void Tohoid::display_bullets(sf::RenderWindow &window)
{
    for (Bullet bull : m_bullets)
    {
        bull.display(window);
    }
}

void Tohoid::move(std::vector <Tohoid> &touhous)
{
    if(m_alive)
    {
        check_keys();

        for (int count{0}; count < m_div; ++count)
        {
            move_bullets();

            check_bullet_border();

            m_sprite.move(m_subframe*m_speed);

            check_border();

            m_smite.setPosition(mirrorize(m_boundary, m_sprite.getPosition(), m_speed));

            relativate();
            rotate();
            accelerate();
            ceiling();

            bullets_hurt(touhous);
            quinergy_restore();
        }

        bullet_shoot();
        danmaku_shoot();

        scale_radius();
    }
}

void Tohoid::display(sf::RenderWindow &window)
{
    if(m_alive)
    {
        display_bullets(window);

        window.draw(m_sprite);

        if (vectralize(m_smite.getPosition()) < squr(m_boundary + m_smite.getLocalBounds().width))
        {
            window.draw(m_smite);
        }
    }
}

sf::Vector2f rotation2direction(const float rotation)
{
    const float divide{M_PI/180};

    return sf::Vector2f(std::sin(divide*rotation), -std::cos(divide*rotation));
}

void set_sprite(const sf::Vector2f &posit, const float rotation, sf::Sprite &sprite)
{
    sprite.setOrigin(0.5f*sprite.getLocalBounds().width, 0.5f*sprite.getLocalBounds().height);
    sprite.setPosition(posit);
    sprite.setRotation(rotation);
}

float squr(const float scalar) noexcept
{
    return scalar*scalar;
}

float vectralize(const sf::Vector2f &vectol) noexcept
{
    return squr(vectol.x) + squr(vectol.y);
}

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed)
{
    if (vectralize(posit) == 0.0f)
    {
        return (1.0f - 2.0f*boundary/std::sqrt(vectralize(speed)))*speed;
    }

    return (1.0f - 2.0f*boundary/std::sqrt(vectralize(posit)))*posit;
}
