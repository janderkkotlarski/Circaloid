#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"

float squr(const float scalar) noexcept;

float vectralize(const sf::Vector2f &vectol) noexcept;

sf::Vector2f rotation2direction(const float rotation);

float direction2rotation(const sf::Vector2f &direction);

sf::Vector2f normalize_direction(const sf::Vector2f &direction);

void set_texture(const std::string &filename, sf::Texture &texture);

void set_sprite(const sf::Vector2f &posit, const float rotation, sf::Texture &texture, sf::Sprite &sprite);

void set_image(const std::string &name, const sf::Vector2f &windims,
               sf::Texture &texture, sf::Sprite &sprite);

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f &posit, const sf::Vector2f &speed);

float sprite_radius(sf::Sprite &sprite);

bool polling(sf::RenderWindow &window, sf::Event &event, bool &loop);

std::vector <float> init_rotats(const int amount);

std::vector <sf::Vector2f> init_posits(const sf::Vector2f &windims,
                                       const std::vector <float> &rotats,
                                       const int amount);

#endif // FUNCTIONS_H
