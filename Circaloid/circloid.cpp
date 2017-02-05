#include "circloid.h"

Circloid::Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed, const float light,
                   const float accel, const float pheta, const float radius, const int points, const sf::Color &color,
                   const int div, const float frame, const std::vector <sf::Keyboard::Key> &keys)
    : m_windims(windims), m_boundary(0.25f*windims.x), m_speed(speed), m_light(squr(light)), m_relative(1.0f), m_accel(accel), m_pheta(pheta),
      m_circle(), m_mircle(), m_bircle(), m_div(div), m_frame(frame), m_subframe(frame/static_cast<float>(div)),
      m_keys(keys), m_keypressed()
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);
    assert(posit.x >= 0.0f);
    assert(posit.y >= 0.0f);
    assert(posit.x <= windims.x);
    assert(posit.y <= windims.y);
    assert(radius >= 0.0f);

    assert(radius <= 0.5f*windims.x);
    assert(radius <= 0.5f*windims.y);

    assert(points > 2);

    assert(m_div > 0);
    assert(m_frame > 0.0f);

    assert(m_keys.size() > 0);

    for (int count{0}; count < static_cast<int>(m_keys.size()); ++count)
    {
        m_keypressed.push_back(false);
    }

    assert(m_keys.size() == m_keypressed.size());

    set_circle(radius, posit, points, color, m_circle);
    set_circle(radius, mirrorize(m_boundary, m_circle.getPosition(), m_speed), points, sf::Color(63, 127, 191), m_mircle);

    set_circle(m_boundary, posit, 100, sf::Color(191, 191, 191), m_bircle);
}

void Circloid::relativate()
{
    if (vectralize(m_speed) < squr(m_light))
    {
        m_relative = sqrt(1 - vectralize(m_speed)/squr(m_light));
    }
    else
    {
        m_relative = 0.0f;
    }

    m_relative += 0.001f;
}

void Circloid::accelerate()
{
    if (m_keypressed[0] || m_keypressed[1])
    {
        const float divide{M_PI/180};

        const sf::Vector2f accer{m_relative*m_accel*sf::Vector2f(std::sin(divide*m_circle.getRotation()),
                                                               -std::cos(divide*m_circle.getRotation()))};

        m_speed += accer;

        if (m_keypressed[1])
        {
            m_speed -= 2.0f*accer;
        }
    }


}

void Circloid::rotate()
{
    if (m_keypressed[2])
    {
        m_circle.rotate(m_relative*m_pheta);
        m_mircle.rotate(m_relative*m_pheta);
    }

    if (m_keypressed[3])
    {
        m_circle.rotate(-m_relative*m_pheta);
        m_mircle.rotate(-m_relative*m_pheta);
    }
}

void Circloid::check_border()
{
    if (vectralize(m_circle.getPosition()) > squr(m_boundary))
    {
        m_circle.setPosition(mirrorize(m_boundary, m_circle.getPosition(), m_speed));
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
        m_circle.move(m_subframe*m_speed);

        check_border();

        m_mircle.setPosition(mirrorize(m_boundary, m_circle.getPosition(), m_speed));

        relativate();
        rotate();
        accelerate();
    }
}

void Circloid::display(sf::RenderWindow &window)
{
    window.draw(m_bircle);

    window.draw(m_circle);

    if (vectralize(m_mircle.getPosition()) < squr(m_boundary + m_mircle.getRadius()))
    {
        window.draw(m_mircle);
    }
}

void set_circle(const float radius, const sf::Vector2f &posit, const int points,
                const sf::Color &color, sf::CircleShape &circle)
{
    circle.setPointCount(points);
    circle.setOrigin(radius,radius);
    circle.setPosition(posit);
    circle.setRadius(radius);
    circle.setFillColor(color);
}

float squr(const float scalar)
{
    return scalar*scalar;
}

float vectralize(const sf::Vector2f &vectol)
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
