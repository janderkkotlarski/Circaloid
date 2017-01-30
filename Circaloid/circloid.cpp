#include "circloid.h"

Circloid::Circloid(const sf::Vector2f &windims, const sf::Vector2f &posit, const sf::Vector2f &speed,
                   const float radius, const sf::Color &color, const int div, const float frame)
    : m_windims(windims), m_speed(speed), m_circle(), m_div(div), m_frame(frame)
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
    assert(m_div > 0);
    assert(m_frame > 0.0f);

    m_circle.setOrigin(radius,radius);
    m_circle.setPosition(posit);
    m_circle.setRadius(radius);
    m_circle.setFillColor(color);
}

void Circloid::move()
{
    m_circle.move(m_frame*m_speed);
}

void Circloid::display(sf::RenderWindow &window)
{
    window.draw(m_circle);
}
