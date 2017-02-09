#include "seeker.h"

Seeker::Seeker(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit,
               const sf::Vector2f &speed, const float &light, const float subframe,
               const int target, const int self)
    : m_boundary(boundary), m_speed(speed), m_accel(0.001f*light),
      m_subframe(subframe), m_target(target), m_circle()
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);

    assert(boundary > 0.0f);

    assert(vectralize(posit) <= squr(boundary));

    assert(light > 0.0f);

    assert(subframe > 0.0f);

    const float part{0.02f};
    assert(part > 0.0f);

    const float radius{part*windims.x};

    set_circle(radius, posit);
}

Seeker::~Seeker()
{
}

void Seeker::set_circle(const float radius, const sf::Vector2f &posit)
{
    const sf::Color color{191, 127, 63};

    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(posit);
    m_circle.setFillColor(color);
}
