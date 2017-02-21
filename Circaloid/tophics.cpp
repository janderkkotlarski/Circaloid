#include "tophics.h"

Tophics::Tophics(const std::string &sprite_name, const sf::Vector2f &posit, const float rotation)
    : m_texture(), m_sprite(), m_smite(),
      m_dexture(), m_direct(), m_disect()
{
    assert(sprite_name != "");

    const std::string direct_name{"Direction_64.png"};
    assert(direct_name != "");

    set_texture(sprite_name, m_texture);

    set_sprite(posit, rotation, m_texture, m_sprite);
    set_sprite(posit, rotation, m_texture, m_smite);

    set_texture(direct_name, m_dexture);

    set_sprite(posit, rotation, m_dexture, m_direct);
    set_sprite(posit, rotation, m_dexture, m_disect);
}

Tophics::~Tophics()
{
}

void Tophics::rotate(const float rotation)
{
    m_sprite.rotate(rotation);
    m_smite.rotate(rotation);
    m_direct.rotate(rotation);
    m_disect.rotate(rotation);
}

void Tophics::move_sprite(const sf::Vector2f &delta_posit)
{
    m_sprite.move(delta_posit);
    m_direct.move(delta_posit);
}

void Tophics::check_border(const float boundary, const sf::Vector2f &speed)
{
    if (vectralize(get_posit()) > squr(boundary))
    {
        m_sprite.setPosition(mirrorize(boundary, get_posit(), speed));
        m_direct.setPosition(get_posit());
    }
}

void Tophics::display(sf::RenderWindow &window, const float boundary)
{
    window.draw(m_direct);
    window.draw(m_sprite);

    if (vectralize(get_mosit()) < squr(m_boundary + m_smite.getLocalBounds().width))
    {
        window.draw(m_disect);
        window.draw(m_smite);
    }
}
