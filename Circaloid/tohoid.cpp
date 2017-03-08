#include "tohoid.h"

Tohoid::Tohoid(const sf::Vector2f &windims, const sf::Vector2f &posit,
               const float rotation, const std::string &image_name,
               const float frame, const std::vector <sf::Keyboard::Key> &keys)
    : m_boundary(0.5f*windims.x),
      m_speed(0.0f*windims),
      m_light(0.3f*m_boundary),
      m_relative(1.0f),
      m_accel(0.002f*m_boundary),
      m_pheta(0.5f*M_PI),
      m_quinergy(1.0f),
      m_questore(0.02f),
      m_tophics(image_name, posit, m_boundary, rotation),
      m_frame(frame),
      m_keys(keys),
      m_bullets(),
      m_bullet_shot(false),
      m_danmaku_shot(false),
      m_alive(true)
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);
    assert(posit.x >= -windims.x);
    assert(posit.y >= -windims.y);
    assert(posit.x <= windims.x);
    assert(posit.y <= windims.y);

    assert(frame > 0.0f);

    assert(m_keys.size() > 0);
}

Tohoid::~Tohoid()
{
}

void Tohoid::relativate()
{
    const float minim{0.25f};
    assert(minim > 0.0f);

    if (vectralize(m_speed) < squr(m_light))
    { m_relative = (1.0f - minim)*sqrt(1 - vectralize(m_speed)/squr(m_light)) + minim; }

    if (m_relative < minim)
    { m_relative = minim; }
}

void Tohoid::accelerate()
{
    const sf::Vector2f accer{m_relative*m_accel*rotation2direction(get_rotate())};

    if (sf::Keyboard::isKeyPressed(m_keys[0]))
    {
        m_speed += accer;
        m_quinergy -= m_frame*m_questore;
    }

    if (sf::Keyboard::isKeyPressed(m_keys[1]))
    {
        m_speed -= accer;
        m_quinergy -= m_frame*m_questore;
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
    float rotation{m_relative*m_pheta};

    if (sf::Keyboard::isKeyPressed(m_keys[2]))
    {
        m_tophics.rotate(rotation);
        m_quinergy -= m_frame*m_questore;
    }

    if (sf::Keyboard::isKeyPressed(m_keys[3]))
    {
        m_tophics.rotate(-rotation);
        m_quinergy -= m_frame*m_questore;
    }
}

void Tohoid::quinergy_restore()
{
    m_quinergy += m_frame*m_questore;

    if (m_quinergy > 1.0f)
    { m_quinergy = 1.0f; }
}

void Tohoid::bullet_shoot()
{
    if (sf::Keyboard::isKeyPressed(m_keys[4]))
    {
        if (!m_bullet_shot)
        {
            const float scale{1.01f};

            const float qi_loss{-0.01f};
            assert(qi_loss < 0.0f);

            m_quinergy += qi_loss;

            m_bullets.push_back(Bullet(m_boundary, get_posit(), m_light,
                                       rotation2direction(get_rotate()), m_frame, bullet_type::normal));

            const sf::Vector2f leap{(scale*get_radius() + scale*m_bullets.back().get_radius())*rotation2direction(get_rotate())};

            m_bullets.back().jump(leap);
            m_bullet_shot = true;
        }
    }
    else
    { m_bullet_shot = false; }
}

void Tohoid::danmaku_shoot()
{
    if (sf::Keyboard::isKeyPressed(m_keys[5]))
    {
        if (!m_danmaku_shot)
        {
            const float scale{1.01f};

            const float qi_loss{-0.07f};
            assert(qi_loss < 0.0f);

            m_quinergy += qi_loss;

            const int number{8};
            assert(number > 1);

            const float delta_rotate{180.0f/static_cast<float>(number)};

            float rotate{(0.5f - static_cast<float>(number/2))*delta_rotate};

            for (int count{0}; count < number; ++count)
            {
                const float rotation{rotate + get_rotate()};
                const sf::Vector2f direction{rotation2direction(rotation)};

                m_bullets.push_back(Bullet(m_boundary, get_posit(), m_light,
                                           direction, m_frame, bullet_type::danmaku));

                const sf::Vector2f leap{(scale*get_radius() + scale*m_bullets.back().get_radius())*direction};

                m_bullets.back().jump(leap);
                rotate += delta_rotate;
            }

            m_danmaku_shot = true;
        }
    }
    else
    { m_danmaku_shot = false; }
}

void Tohoid::seeker_shoot(std::vector <Tohoid> &touhous)
{
    if (sf::Keyboard::isKeyPressed(m_keys[6]))
    {
        if (!m_seeker_shot && (m_seeker.size() < 1))
        {
            const float scale{1.01f};

            const float qi_loss{-0.25f};
            assert(qi_loss < 0.0f);

            m_quinergy += qi_loss;

            m_seeker.push_back(Seeker(m_boundary, get_posit(), m_speed, m_frame,
                                      touhou_self(touhous), touhou_target(touhous)));

            const sf::Vector2f leap{(scale*get_radius() + scale*m_seeker.back().get_radius())*rotation2direction(get_rotate())};

            m_seeker.back().jump(leap);
            m_seeker_shot = true;
        }
    }
    else
    { m_seeker_shot = false; }
}

void Tohoid::move_bullets(std::vector <Tohoid> &touhous)
{
    std::vector <sf::Vector2f> posits{touhous2posits(touhous)};
    std::vector <bool> alives{touhous2alives(touhous)};

    for (int count{0}; count < static_cast<int>(m_bullets.size()); ++count)
    {
        m_bullets[count].bullet_speed(m_light, alives, posits, get_posit());
        m_bullets[count].move();
    }

    // for (auto bullet : m_bullets)
    // {
    //     bullet.bullet_speed(m_light, alives, posits, get_posit());
    //     bullet.move();
    // }

    // std::for_each(std::begin(m_bullets),
    //               std::end(m_bullets),
    //               []()
    //               { move(); });

    for (int count(0); count < static_cast<int>(m_seeker.size()); ++count)
    {
        const int target{m_seeker[count].get_target()};

        m_seeker[count].set_speed(posits[target]);
        m_seeker[count].move();
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

void Tohoid::check_seeker_border()
{
    if (m_seeker.size() > 0)
    {
        for (int count{0}; count < static_cast<int>(m_seeker.size()); ++count)
        {
            if (vectralize(m_seeker[count].get_posit()) > squr(m_boundary - m_seeker[count].get_radius()))
            {
                m_seeker[count] = m_seeker.back();
                m_seeker.pop_back();
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
        assert(qi_hurt < 0.0f);

        const float scale{0.85f};

        for (int iter{0}; iter < static_cast<int>(touhous.size()); ++iter)
        {
            if (touhous[iter].get_vivid())
            {
                for (int count{0}; count < static_cast<int>(m_bullets.size()); ++count)
                {
                    const float dist_2{vectralize(m_bullets[count].get_posit() - touhous[iter].get_posit())};
                    const float mist_2{vectralize(m_bullets[count].get_posit() - touhous[iter].get_mosit())};

                    const float radi_2{squr(m_bullets[count].get_radius() + scale*touhous[iter].get_radius())};
                    const float madi_2{squr(m_bullets[count].get_radius() + scale*touhous[iter].get_madius())};

                    const float bound_2{squr(m_boundary + scale*touhous[iter].get_madius())};
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

void Tohoid::seeker_hurt(std::vector <Tohoid> &touhous)
{
    if ((m_seeker.size() > 0) && (touhous.size() > 0))
    {
        const float qi_hurt{-1.01f};
        assert(qi_hurt < 0.0f);

        const float scale{0.85f};
        assert(scale > 0.0f);

        for (int iter{0}; iter < static_cast<int>(touhous.size()); ++iter)
        {
            if (touhous[iter].get_vivid())
            {
                for (int count{0}; count < static_cast<int>(m_seeker.size()); ++count)
                {
                    const float dist_2{vectralize(m_seeker[count].get_posit() - touhous[iter].get_posit())};
                    const float mist_2{vectralize(m_seeker[count].get_posit() - touhous[iter].get_mosit())};

                    const float radi_2{squr(m_seeker[count].get_radius() + scale*touhous[iter].get_radius())};
                    const float madi_2{squr(m_seeker[count].get_radius() + scale*touhous[iter].get_madius())};

                    const float bound_2{squr(m_boundary + scale*touhous[iter].get_madius())};
                    const float mosit_2{vectralize(touhous[iter].get_mosit())};

                    if ((dist_2 <= radi_2) ||
                        ((mist_2 <= madi_2) && (mosit_2 <= bound_2)))
                    {
                        m_seeker[count] = m_seeker.back();
                        m_seeker.pop_back();
                        touhous[iter].qi_damage(qi_hurt);
                        --count;
                    }
                }
            }
        }
    }
}

void Tohoid::move_tophics()
{
    const sf::Vector2f del_pos{m_frame*m_speed};

    m_tophics.move_sprite(del_pos);
    m_tophics.check_border(del_pos);
    m_tophics.move_smite(del_pos);
}

void Tohoid::display_bullets(sf::RenderWindow &window)
{
    for (Bullet bull : m_bullets)
    { bull.display(window); }

    for (Seeker seek : m_seeker)
    { seek.display(window); }
}

void Tohoid::move(std::vector <Tohoid> &touhous)
{
    if (m_alive)
    {


        move_bullets(touhous);

        check_bullet_border();
        check_seeker_border();

        move_tophics();

        accelerate();

        relativate();
        rotate();

        ceiling();

        bullets_hurt(touhous);
        seeker_hurt(touhous);
        quinergy_restore();

        bullet_shoot();
        danmaku_shoot();
        seeker_shoot(touhous);

        scale_radius();
    }
}

void Tohoid::display(sf::RenderWindow &window)
{
    if(m_alive)
    {
        display_bullets(window);
        m_tophics.display(window);
    }
}

int Tohoid::touhou_self(std::vector<Tohoid> &touhous)
{
    int self{-1};

    for (int count{0}; count < static_cast<int>(touhous.size()); ++count)
    {
        if (vectralize(touhous[count].get_posit() - get_posit()) < 10.0f)
        { self = count; }
    }

    return self;
}

int Tohoid::touhou_target(std::vector <Tohoid> &touhous)
{
    int target{-1};

    const int self{touhou_self(touhous)};

    float max_2{1.0e10f};

    for (int count{0}; count < static_cast<int>(touhous.size()); ++count)
    {
        if ((count != self) && touhous[count].get_vivid())
        {
            const float dist_2{vectralize(touhous[count].get_posit() - touhous[self].get_posit())};

            if (dist_2 < max_2)
            {
                target = count;
                max_2 = dist_2;
            }
        }
    }

    return target;
}

std::vector <sf::Vector2f> touhous2posits(std::vector <Tohoid> &touhous)
{
    std::vector <sf::Vector2f> posits;

    for (Tohoid toho : touhous)
    { posits.push_back(toho.get_posit()); }

    return posits;
}

std::vector <bool> touhous2alives(std::vector <Tohoid> &touhous)
{
    std::vector <bool> alives;

    for (Tohoid toho : touhous)
    { alives.push_back(toho.get_vivid()); }

    return alives;
}


