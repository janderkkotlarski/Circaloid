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

