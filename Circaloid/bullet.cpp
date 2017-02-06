#include "bullet.h"

Bullet::Bullet(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit, const float veloc,
               const sf::Vector2f &direction, const float subframe, const sf::Color &color)
    : m_boundary(boundary), m_veloc(veloc), m_direction(direction), m_subframe(subframe),
      m_circle()
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);

    assert(boundary > 0.0f);

    assert(veloc >= 0.0f);

    assert(subframe > 0.0f);

    const float part{0.01f};
    assert(part > 0.0f);

    const float radius{part*windims.x};

    set_circle(radius, posit, color);


}

void Bullet::set_circle(const float radius, const sf::Vector2f &posit, const sf::Color &color)
{
    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(posit);
    m_circle.setFillColor(color);
}
