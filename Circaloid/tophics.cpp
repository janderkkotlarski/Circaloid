#include "tophics.h"

Tophics::Tophics(const std::string& sprite_name, const sf::Vector2f& posit,
                 const float boundary, const float rotation)
    : m_boundary(boundary),
      m_texture(), m_sprite(), m_smite(),
      m_dexture(), m_direct(), m_disect()
{
    assert(sprite_name != "");

    set_texture(sprite_name, m_texture);

    set_sprite(posit, rotation, m_texture, m_sprite);
    set_sprite(posit, rotation, m_texture, m_smite);

    const std::string folder
    { "/Circaloid/Resources/" };
    assert(folder != "");

    const std::string direct_name
    { "Direction_64.png" };
    assert(direct_name != "");


    extract_file(folder, direct_name);
    set_texture(direct_name, m_dexture);

    set_sprite(posit, rotation, m_dexture, m_direct);
    set_sprite(posit, rotation, m_dexture, m_disect);
}

Tophics::~Tophics()
{}

void Tophics::init_sprite()
{
    set_sprite(get_posit(), get_rotate(), m_texture, m_sprite);
    set_sprite(get_posit(), get_rotate(), m_texture, m_smite);
}

void Tophics::init_direct()
{
    set_sprite(get_posit(), get_rotate(), m_dexture, m_direct);
    set_sprite(get_posit(), get_rotate(), m_dexture, m_disect);
}

void Tophics::rotate(const float rotation)
{
    m_sprite.rotate(rotation);
    m_smite.rotate(rotation);
    m_direct.rotate(rotation);
    m_disect.rotate(rotation);
}

void Tophics::move_sprite(const sf::Vector2f& delta_posit)
{
    m_sprite.move(delta_posit);
    m_direct.move(delta_posit);
}

void Tophics::check_border(const sf::Vector2f& speed)
{
    if (vectralize(get_posit()) > squr(m_boundary))
    {
        m_sprite.setPosition(mirrorize(m_boundary, get_posit(), speed));
        m_direct.setPosition(get_posit());
    }
}

void Tophics::move_smite(const sf::Vector2f& speed)
{
    m_smite.setPosition(mirrorize(m_boundary, get_posit(), speed));
    m_disect.setPosition(get_mosit());
}

void Tophics::set_scale(const float scale)
{
    m_sprite.setScale(scale, scale);
    m_smite.setScale(scale, scale);
}

void Tophics::display(sf::RenderWindow& window)
{
    window.draw(m_direct);
    window.draw(m_sprite);

    if (vectralize(get_mosit()) < squr(m_boundary + m_smite.getLocalBounds().width))
    {
        window.draw(m_disect);
        window.draw(m_smite);
    }
}
