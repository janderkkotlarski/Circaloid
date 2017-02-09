#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

#include "SFML/Graphics.hpp"

float squr(const float scalar) noexcept;

float vectralize(const sf::Vector2f &vectol) noexcept;

sf::Vector2f rotation2direction(const float rotation);

float direction2rotation(const sf::Vector2f &direction);

sf::Vector2f normalize_direction(const sf::Vector2f &direction);

void set_sprite(const sf::Vector2f &posit, const float rotation, sf::Sprite &sprite);

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed);

#endif // FUNCTIONS_H