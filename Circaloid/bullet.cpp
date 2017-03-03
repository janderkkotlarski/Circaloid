#include "bullet.h"

Bullet::Bullet(const sf::Vector2f &windims, const float boundary, const sf::Vector2f &posit, const float veloc,
               const sf::Vector2f &direction, const float frame, const bullet_type &type)
    : m_boundary(boundary), m_veloc(veloc), m_direction(direction), m_frame(frame),
      m_circle(), m_type(type)
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);

    assert(boundary > 0.0f);
    assert(vectralize(posit) <= squr(boundary));

    assert(veloc >= 0.0f);

    assert(frame > 0.0f);

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

void Bullet::bullet_speed(const float light, const std::vector <bool> &alives, const std::vector <sf::Vector2f> &targets,
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
            danmaku_transform(alives, targets, otaku);
            m_veloc = light;
            m_type = bullet_type::normal;
        }
    }
}

void Bullet::danmaku_transform(const std::vector <bool> alives,
                               const std::vector <sf::Vector2f> &targets, const sf::Vector2f &otaku)
{
    int marked{-1};
    assert(marked == -1);

    float min_2{1.0e10f};
    assert(min_2 >= 1.0e10f);

    const float max_2{10.0f};
    assert(max_2 <= 10.0f);

    for (int count{0}; count < static_cast<int>(targets.size()); ++count)
    {
        const float devi_2{vectralize(targets[count] - otaku)};

        if ((devi_2 > max_2) && alives[count])
        {
            const float dist_2{vectralize(targets[count] - get_posit())};

            if(dist_2 < min_2)
            {
                min_2 = dist_2;
                marked = count;
            }
        }
    }

    if (marked != -1)
    {
        set_direction(normalize_direction(targets[marked] - get_posit()));
    }
}
