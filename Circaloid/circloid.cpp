#include "circloid.h"

Circloid::Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
                   const float accel, const float pheta, const std::string &image_name,
                   const int div, const float frame, const std::vector <sf::Keyboard::Key> &keys)
    : m_windims(windims), m_boundary(0.5f*windims.x), m_speed(speed), m_light(squr(light)), m_relative(1.0f),
      m_accel(accel), m_pheta(pheta), m_quinergy(1.0f), m_questore(0.02f), m_quove(-0.02f), m_texture(), m_sprite(), m_smite(),
      m_div(div), m_frame(frame), m_subframe(frame/static_cast<float>(div)),
      m_keys(keys), m_keypressed()
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

    set_sprite(posit, m_sprite);
    set_sprite(posit, m_smite);
}

void Circloid::relativate()
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

void Circloid::accelerate()
{
    if (m_keypressed[0] || m_keypressed[1])
    {
        const float divide{M_PI/180};

        const sf::Vector2f accer{m_relative*m_accel*sf::Vector2f(std::sin(divide*m_sprite.getRotation()),
                                                                 -std::cos(divide*m_sprite.getRotation()))};

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

void Circloid::ceiling()
{
    if (vectralize(m_speed) > squr(m_light))
    {
        m_speed *= m_light/std::sqrt(vectralize(m_speed));
    }
}

void Circloid::rotate()
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

void Circloid::scale_radius()
{
    m_sprite.setScale(m_quinergy, m_quinergy);
    m_smite.setScale(m_quinergy, m_quinergy);
}

void Circloid::quinergy_restore()
{
    m_quinergy += m_subframe*m_questore;

    if (m_quinergy > 1.0f)
    {
        m_quinergy = 1.0f;
    }
}

void Circloid::check_border()
{
    if (vectralize(m_sprite.getPosition()) > squr(m_boundary))
    {
        m_sprite.setPosition(mirrorize(m_boundary, m_sprite.getPosition(), m_speed));
    }
}

void Circloid::check_keys()
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

void Circloid::move()
{
    check_keys();

    for (int count{0}; count < m_div; ++count)
    {
        m_sprite.move(m_subframe*m_speed);

        check_border();

        m_smite.setPosition(mirrorize(m_boundary, m_sprite.getPosition(), m_speed));

        relativate();
        rotate();
        accelerate();
        ceiling();
        quinergy_restore();
    }

    scale_radius();
}

void Circloid::display(sf::RenderWindow &window)
{
    window.draw(m_sprite);

    if (vectralize(m_smite.getPosition()) < squr(m_boundary + m_smite.getLocalBounds().width))
    {
        window.draw(m_smite);
    }
}

void set_sprite(const sf::Vector2f &posit, sf::Sprite &sprite)
{
    sprite.setOrigin(0.5f*sprite.getLocalBounds().width, 0.5f*sprite.getLocalBounds().height);
    sprite.setPosition(posit);
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
