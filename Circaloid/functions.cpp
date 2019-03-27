#include "functions.h"

float squaring_scalar(const float scalar) noexcept
{ return scalar*scalar; }

float squaring_vector(const sf::Vector2f& vector) noexcept
{ return squaring_scalar(vector.x) + squaring_scalar(vector.y); }

float averaging_vector(const sf::Vector2f& vector)
{ return 0.5f*(vector.x + vector.y); }

sf::Vector2f rotation_to_vector(const float rotation)
{
    const float divide
    { static_cast<float>(M_PI)/180.0f };
    return sf::Vector2f(std::sin(divide*rotation), -std::cos(divide*rotation));
}

float vector_to_rotation(const sf::Vector2f& vector)
{
    const float multiply
    { 180.0f/static_cast<float>(M_PI) };

    float rotation
    { 0.0f };

    if (vector.x == 0.0f)
    {
        if (vector.y < 0.0f)
        { rotation = 90.0f; }
        else
        { rotation = -90.0f; }
    }
    else
    {
        if (vector.y < 0.0f)
        { rotation = multiply*std::atan(vector.y/vector.x); }
        else
        { rotation = -multiply*std::atan(vector.y/vector.x); }
    }

    return rotation;
}

sf::Vector2f normalize_vector(const sf::Vector2f& vector)
{
    assert(vector.x != 0.0f &&
           vector.y != 0.0f);

    return vector/std::sqrt(squaring_vector(vector));
}

void set_texture(const std::string& filename,
                 sf::Texture& texture)
{
    assert(filename != "");

    if (!texture.loadFromFile(filename))
    { std::cerr << filename << " not found!\n"; }

    texture.setSmooth(true);
}

void set_sprite(const sf::Vector2f& position,
                const float rotation,
                sf::Texture& texture,
                sf::Sprite &sprite)
{    
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*sprite.getLocalBounds().width, 0.5f*sprite.getLocalBounds().height);
    sprite.setPosition(position);
    sprite.setRotation(rotation);
}

void set_image(const std::string& name,
               const sf::Vector2f& window_dimensions,
               sf::Texture& texture,
               sf::Sprite& sprite)
{
    assert(name != "");

    if (!texture.loadFromFile(name))
    { std::cerr << name << "not found!\n"; }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*window_dimensions);
    sprite.setPosition(0.0f*window_dimensions);
}

sf::Vector2f mirrorize(const float boundary_radius,
                       const sf::Vector2f& position,
                       const sf::Vector2f& speed)
{
  if (squaring_vector(position) == 0.0f)
    {
      if (squaring_vector(speed) == 0.0f)
      { return 2.0f*boundary_radius*sf::Vector2f{1.0f, 0.0f}; }

      return (1.0f - 2.0f*boundary_radius/std::sqrt(squaring_vector(speed)))*speed;
    }

    return (1.0f - 2.0f*boundary_radius/std::sqrt(squaring_vector(position)))*position;
}

float sprite_radius(sf::Sprite& sprite)
{ return 0.25f*(sprite.getGlobalBounds().width + sprite.getGlobalBounds().height); }

bool poll_reset_quit(sf::RenderWindow& window,
             sf::Event& event,
             bool& loop)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        {
            loop = false;

            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return true;
            }
        }
    }

    return false;
}

std::vector <float> initialize_rotations(const int amount)
{
    std::vector <float> rotations;

    for (int count {0}; count < amount; ++count)
    { rotations.push_back(static_cast<float>(count)*360.0f/static_cast<float>(amount)); }

    assert(rotations.size() == static_cast<unsigned>(amount));
    return rotations;
}

std::vector <sf::Vector2f> initialize_positions(const sf::Vector2f& window_dimensions,
                                                const std::vector <float>& rotations,
                                                const int amount)
{
    std::vector <sf::Vector2f> positions;

    const float rel_dist
    { 0.7f };
    assert(rel_dist > 0.0f);

    for (unsigned int count {0}; count < static_cast<unsigned int>(amount); ++count)
    { positions.push_back(-0.7f*averaging_vector(window_dimensions)*rotation_to_vector(rotations[count])); }

    assert(positions.size() == static_cast<unsigned>(amount));
    return positions;
}

void cout_vect2f(const sf::Vector2f& vectol)
{ std::cout << '[' << vectol.x << ':' << vectol.y << "]\n"; }

void copy_file(const std::string& folder,
                  const std::string& name)
{
    const QString home_path
    { QDir::current().absolutePath() };

    // dir_path_couter(home_path);

    const QString home_name
    { home_path + QString::fromStdString("/" + name) };

    // dir_path_couter(home_name);

    QDir base_dir
    { QDir::current() };

    base_dir.cdUp();

    QString base_path
    { base_dir.absolutePath() };

    // dir_path_couter(base_path);

    const QString base_name
    { base_path + QString::fromStdString(folder + name) };

    // dir_path_couter(base_name);

    assert(QFile::exists(base_name));
    check_path(base_name);

    QFile file(base_name);

    file.copy(home_name);

    assert(QFile::exists(home_name));
    check_path(home_name);
}

void copy_file_vector(const std::string& folder,
                         const std::vector <std::string>& names)
{
    assert(names.size() > 0);

    for (const std::string& name: names)
    { copy_file(folder, name); }
}

void dir_path_couter(const QString& dir_path) noexcept
{ std::cout << dir_path.toStdString() << '\n'; }

void check_path(const QString& dir_path)
{
   if (!QFile::exists(dir_path))
   { std::cout << dir_path.toStdString() << " was not found.\n"; }
}
