#include "circloid.h"

Circloid::Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed,
                   const float radius, const sf::Color &color, const int div, const float frame)
    : m_windims(windims), m_boundary(0.05f*windims.x), m_speed(speed), m_circle(), m_mircle(), m_bircle(),
      m_div(div), m_frame(frame), m_subframe(frame/static_cast<float>(div))
{
    // std::cout << windims.x << "\n";
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);
    assert(posit.x >= 0.0f);
    assert(posit.y >= 0.0f);
    assert(posit.x <= windims.x);
    assert(posit.y <= windims.y);
    assert(radius >= 0.0f);

    // std::cout << radius << "\n";
    // std::cout << m_windims.x << "\n";
    assert(radius <= 0.5f*windims.x);
    assert(radius <= 0.5f*windims.y);

    assert(m_div > 0);
    assert(m_frame > 0.0f);

    set_circle(radius, posit, color, m_circle);
    set_circle(radius, mirrorize(m_boundary, m_circle.getPosition(), m_speed), sf::Color(63, 127, 191), m_mircle);



    set_circle(m_boundary, posit, sf::Color(191, 191, 191), m_bircle);
}

void Circloid::check_border()
{
    if (vectralize(m_circle.getPosition()) > squr(m_boundary))
    {
        std::cout << vectralize(m_circle.getPosition()) << "\n";
        std::cout << squr(m_boundary) << "\n";

        m_circle.setPosition(mirrorize(m_boundary, m_circle.getPosition(), m_speed));

    }
}

void Circloid::move()
{
    m_circle.move(m_frame*m_speed);

    check_border();

    m_mircle.setPosition(mirrorize(m_boundary, m_circle.getPosition(), m_speed));
}

void Circloid::display(sf::RenderWindow &window)
{
    window.draw(m_bircle);
    window.draw(m_circle);
    window.draw(m_mircle);
}

void set_circle(const float radius, const sf::Vector2f &posit, const sf::Color &color,
                          sf::CircleShape &circle)
{
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
    // return (1.0f - 2.0f*boundary/std::sqrt(vectralize(posit)))*posit;

    if (vectralize(posit) == 0.0f)
    {
        return (1.0f - 2.0f*boundary/std::sqrt(vectralize(speed)))*speed;
    }


    return (1.0f - 2.0f*boundary/std::sqrt(vectralize(posit)))*posit;
}
