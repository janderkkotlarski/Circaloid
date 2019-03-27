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

/// Square of a scalar
float squaring_scalar(const float scalar) noexcept;

/// Absolute square of a vector
float squaring_vector(const sf::Vector2f& vector) noexcept;

/// Average of x and y of a vector
float averaging_vector(const sf::Vector2f& vector);

/// Change a scalar rotation into a directional unit vector
sf::Vector2f rotation_to_vector(const float rotation);

/// Change a vector into a scalar rotation
float vector_to_rotation(const sf::Vector2f& vector);

/// Turn a vector into a unit vector having the same direction
sf::Vector2f normalize_vector(const sf::Vector2f& vector);

/// Make a texture from a file
void set_texture(const std::string& filename, sf::Texture& texture);

/// Make a sprite using a postion, rotation and a texture
void set_sprite(const sf::Vector2f& position,
                const float rotation,
                sf::Texture& texture,
                sf::Sprite& sprite);

/// Make an image sprite using a name
void set_image(const std::string& name,
               const sf::Vector2f& window_dimensions,
               sf::Texture& texture,
               sf::Sprite& sprite);

/// Mirror position on boundary based upon position or speed
sf::Vector2f mirrorize(const float boundary_radius,
                       const sf::Vector2f& posit,
                       const sf::Vector2f& speed);

/// Calculate the radius of a sprite with a circle
/// Actually takes half of sprite width and height and averages them
float sprite_radius(sf::Sprite& sprite);

/// See whether the Delete of Escape button if pressed to either reset or quit
bool poll_reset_quit(sf::RenderWindow& window,
             sf::Event& event,
             bool& loop);

/// Initialize touhoid rotations
std::vector <float> initialize_rotations(const int amount);

/// Initializing touhoid positions
std::vector <sf::Vector2f> initialize_positions(const sf::Vector2f& window_dimensions,
                                                const std::vector <float>& rotations,
                                                const int amount);

/// Displaying a vector2f on the terminal
void cout_vector2f(const sf::Vector2f& vector);

/// Copy a file from a folder to another folder
void copy_file(const std::string& folder_name,
               const std::string& file_name);

/// Copy a vector of files using previous function
void copy_file_vector(const std::string& folder_name,
                      const std::vector <std::string>& file_names);

/// Displaying a directory path on the terminal
void cout_directory_path(const QString& directory_path) noexcept;

/// Checking the validity of a directory path
void check_directory_path(const QString& directory_path);

#endif // FUNCTIONS_H
