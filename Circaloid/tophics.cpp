#include "tophics.h"

Tophics::Tophics(const std::string& foldername,
                 const std::string& filename,
                 const sf::Vector2f& posit,
                 const float boundary,
                 const float rotation)
    : m_foldername(foldername),
      m_boundary(boundary),
      m_texture(),
      m_sprite(),
      m_smite(),
      m_dexture(),
      m_direct(),
      m_disect()
{
    assert(m_foldername != "");
    assert(filename != "");

    set_texture(filename, m_texture);

    set_sprite(posit, rotation, m_texture, m_sprite);
    set_sprite(posit, rotation, m_texture, m_smite);

    const std::string direct_name
    { "Direction_64.png" };
    assert(direct_name != "");

    set_texture(direct_name, m_dexture);

    set_sprite(posit, rotation, m_dexture, m_direct);
    set_sprite(posit, rotation, m_dexture, m_disect);
}

Tophics::~Tophics()
{}

void Tophics::init_sprite()
{
    set_sprite(get_position(), get_rotate(), m_texture, m_sprite);
    set_sprite(get_position(), get_rotate(), m_texture, m_smite);
}

void Tophics::init_direct()
{
    set_sprite(get_position(), get_rotate(), m_dexture, m_direct);
    set_sprite(get_position(), get_rotate(), m_dexture, m_disect);
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
    if (squaring_vector(get_position()) > squaring_scalar(m_boundary))
    {
        m_sprite.setPosition(mirrorize(m_boundary, get_position(), speed));
        m_direct.setPosition(get_position());
    }
}

void Tophics::move_smite(const sf::Vector2f& speed)
{
    m_smite.setPosition(mirrorize(m_boundary, get_position(), speed));
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

    if (squaring_vector(get_mosit()) < squaring_scalar(m_boundary + m_smite.getLocalBounds().width))
    {
        window.draw(m_disect);
        window.draw(m_smite);
    }
}
