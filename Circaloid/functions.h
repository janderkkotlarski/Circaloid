#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "QDir"
#include "QFile"

#include "SFML/Graphics.hpp"

/// square of a scalar
float squaring_scalar(const float scalar) noexcept;

/// absolute square of a vector
float squaring_vector(const sf::Vector2f& vectol) noexcept;

float average(const sf::Vector2f& vectol);

sf::Vector2f rotation2direction(const float rotation);

float direction2rotation(const sf::Vector2f& direction);

sf::Vector2f normalize_direction(const sf::Vector2f& direction);

void set_texture(const std::string& filename, sf::Texture& texture);

void set_sprite(const sf::Vector2f& posit,
                const float rotation,
                sf::Texture& texture,
                sf::Sprite& sprite);

void set_image(const std::string& name,
               const sf::Vector2f& windims,
               sf::Texture& texture,
               sf::Sprite& sprite);

sf::Vector2f mirrorize(const float boundary,
                       const sf::Vector2f& posit,
                       const sf::Vector2f& speed);

float sprite_radius(sf::Sprite& sprite);

/// See whether to reset or quit
bool poll_reset_quit(sf::RenderWindow& window,
             sf::Event& event,
             bool& loop);

/// Initialize touhoid rotations
std::vector <float> init_rotats(const int amount);

/// Initializing touhoid positions
std::vector <sf::Vector2f> init_posits(const sf::Vector2f& windims,
                                       const std::vector <float>& rotats,
                                       const float amount);

///
void cout_vect2f(const sf::Vector2f& vectol);

/// Copy file from folder to other folder
void copy_file(const std::string& folder,
                  const std::string& name);

void copy_file_vector(const std::string& folder,
                         const std::vector <std::string>& names);

void dir_path_couter(const QString& dir_path) noexcept;

void check_path(const QString& dir_path);

#endif // FUNCTIONS_H
