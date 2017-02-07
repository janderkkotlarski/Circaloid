#include "bullet.h"

Bullet::Bullet(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit, const float veloc,
               const sf::Vector2f &direction, const float subframe, const bullet_type &type)
    : m_boundary(boundary), m_veloc(veloc), m_direction(direction), m_subframe(subframe),
      m_circle(), m_type(type)
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);

    assert(boundary > 0.0f);

    assert(veloc >= 0.0f);

    assert(subframe > 0.0f);

    const float part{0.01f};
    assert(part > 0.0f);

    const float radius{part*windims.x};

    set_circle(radius, posit);
}

Bullet::~Bullet()
{
}

void Bullet::set_circle(const float radius, const sf::Vector2f &posit)
{
    const sf::Color color{191, 63, 63};

    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(posit);
    m_circle.setFillColor(color);
}

void Bullet::bullet_speed(const float light, const std::vector <sf::Vector2f> &targets,
                          const sf::Vector2f &otaku)
{
    if (m_type == bullet_type::danmaku)
    {
        const float delta_veloc{-0.0001f*light};

        m_veloc += delta_veloc;
    }

    if (m_veloc < 0.0f)
    {
        m_veloc = 0.0f;

        if (m_type == bullet_type::danmaku)
        {

        }
    }
}

void Bullet::danmaku_transform()
{

}
