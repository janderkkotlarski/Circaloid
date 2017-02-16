#include "functions.h"

float squr(const float scalar) noexcept { return scalar*scalar; }

float vectralize(const sf::Vector2f &vectol) noexcept { return squr(vectol.x) + squr(vectol.y); }

sf::Vector2f rotation2direction(const float rotation)
{
    const float divide{M_PI/180};
    return sf::Vector2f(std::sin(divide*rotation), -std::cos(divide*rotation));
}

float direction2rotation(const sf::Vector2f &direction)
{
    const float multiply{180/M_PI};

    if (direction.x == 0.0f)
    {
        if (direction.y < 0.0f)
        { return 90; }
        else
        { return -90; }
    }
    else
    {
        if (direction.y < 0.0f)
        { return multiply*std::atan(direction.y/direction.x); }
        else
        { return -multiply*std::atan(direction.y/direction.x); }
    }
}

sf::Vector2f normalize_direction(const sf::Vector2f &direction)
{ return direction/std::sqrt(vectralize(direction)); }

void set_texture(const std::string &filename, sf::Texture &texture)
{
    assert(filename != "");

    if (!texture.loadFromFile(filename))
    { std::cerr << filename << " not found!\n"; }

    texture.setSmooth(true);
}

void set_sprite(const sf::Vector2f &posit, const float rotation,
                sf::Texture &texture, sf::Sprite &sprite)
{
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*sprite.getLocalBounds().width, 0.5f*sprite.getLocalBounds().height);
    sprite.setPosition(posit);
    sprite.setRotation(rotation);
}

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed)
{
    if (vectralize(posit) == 0.0f) { return (1.0f - 2.0f*boundary/std::sqrt(vectralize(speed)))*speed; }

    return (1.0f - 2.0f*boundary/std::sqrt(vectralize(posit)))*posit;
}
