#include "seeker.h"

Seeker::Seeker(const float boundary,
               const sf::Vector2f& posit,
               const sf::Vector2f& speed,
               const float frame,
               const int self,
               const int target)
    : m_speed(speed),
      m_accel(1.0f*boundary),
      m_frame(frame),
      m_self(self),
      m_target(target),
      m_circle()
{
    assert(boundary > 0.0f);
    assert(squaring_vector(posit) <= squaring_scalar(boundary));
    assert(frame > 0.0f);

    assert(m_accel > 0.0f);

    const float part
    { 0.05f };
    assert(part > 0.0f);

    const float radius
    { part*boundary };
    set_circle(radius, posit);
}

Seeker::~Seeker()
{}

void Seeker::set_circle(const float radius,
                        const sf::Vector2f& posit)
{
    const sf::Color color
    { 191, 127, 63 };
    assert(color != sf::Color(0, 0, 0));

    m_circle.setRadius(radius);
    m_circle.setOrigin(radius, radius);
    m_circle.setPosition(posit);
    m_circle.setFillColor(color);
}

void Seeker::set_speed(const sf::Vector2f& target_posit)
{
    if (m_target >= 0)
    {
        const sf::Vector2f target_dist
        { target_posit - get_posit() };
        const sf::Vector2f to_target
        { normalize_direction(target_dist) };

        m_speed += m_frame*m_accel*to_target;
    }
}
