#include "functions.h"

float squr(const float scalar) noexcept
{ return scalar*scalar; }

float vectralize(const sf::Vector2f& vectol) noexcept
{ return squr(vectol.x) + squr(vectol.y); }

float average(const sf::Vector2f& vectol)
{ return 0.5f*(vectol.x + vectol.y); }

sf::Vector2f rotation2direction(const float rotation)
{
    const float divide
    { M_PI/180.0f };
    return sf::Vector2f(std::sin(divide*rotation), -std::cos(divide*rotation));
}

float direction2rotation(const sf::Vector2f& direction)
{
    const float multiply
    { 180.0f/M_PI };

    float rotation
    { 0.0f };

    if (direction.x == 0.0f)
    {
        if (direction.y < 0.0f)
        { rotation = 90.0f; }
        else
        { rotation = -90.0f; }
    }
    else
    {
        if (direction.y < 0.0f)
        { rotation = multiply*std::atan(direction.y/direction.x); }
        else
        { rotation = -multiply*std::atan(direction.y/direction.x); }
    }

    return rotation;
}

sf::Vector2f normalize_direction(const sf::Vector2f& direction)
{
    assert(direction.x != 0.0f &&
           direction.y != 0.0f);

    return direction/std::sqrt(vectralize(direction));
}

void set_texture(const std::string& filename, sf::Texture& texture)
{
    assert(filename != "");

    if (!texture.loadFromFile(filename))
    { std::cerr << filename << " not found!\n"; }

    texture.setSmooth(true);
}

void set_sprite(const sf::Vector2f& posit, const float rotation,
                sf::Texture& texture, sf::Sprite &sprite)
{    
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*sprite.getLocalBounds().width, 0.5f*sprite.getLocalBounds().height);
    sprite.setPosition(posit);
    sprite.setRotation(rotation);
}

void set_image(const std::string& name, const sf::Vector2f& windims,
               sf::Texture& texture, sf::Sprite& sprite)
{
    assert(name != "");

    if (!texture.loadFromFile(name))
    { std::cerr << name << "not found!\n"; }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*windims);
    sprite.setPosition(0.0f*windims);
}

sf::Vector2f mirrorize(const float boundary, const sf::Vector2f& posit,
                       const sf::Vector2f& speed)
{
    if (vectralize(posit) == 0.0f)
    { return (1.0f - 2.0f*boundary/std::sqrt(vectralize(speed)))*speed; }

    return (1.0f - 2.0f*boundary/std::sqrt(vectralize(posit)))*posit;
}

float sprite_radius(sf::Sprite& sprite)
{ return 0.25f*(sprite.getGlobalBounds().width + sprite.getGlobalBounds().height); }

bool polling(sf::RenderWindow& window, sf::Event& event,
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

std::vector <float> init_rotats(const int amount)
{
    std::vector <float> rotats;

    for (int count {0}; count < amount; ++count)
    { rotats.push_back(static_cast<float>(count)*360.0f/static_cast<float>(amount)); }

    assert(rotats.size() == static_cast<unsigned>(amount));
    return rotats;
}

std::vector <sf::Vector2f> init_posits(const sf::Vector2f& windims,
                                       const std::vector <float>& rotats,
                                       const float amount)
{
    std::vector <sf::Vector2f> posits;

    const float rel_dist
    { 0.7f };
    assert(rel_dist > 0.0f);

    for (int count {0}; count < amount; ++count)
    { posits.push_back(-0.7f*average(windims)*rotation2direction(rotats[count])); }

    assert(posits.size() == static_cast<unsigned>(amount));
    return posits;
}

void cout_vect2f(const sf::Vector2f& vectol)
{ std::cout << '[' << vectol.x << ':' << vectol.y << "]\n"; }

void extract_file(const std::string& folder,
                  const std::string& name)
{
    QDir home_dir
    { QDir::current() };

    const QString home_path
    { home_dir.absolutePath() };

    QDir base_dir
    { QDir::current() };

    base_dir.cdUp();

    QString base_path
    { base_dir.absolutePath() };

    QString q_folder
    { QString::fromStdString(folder) };

    QString slash
    { QString::fromStdString("/") };

    QString q_name
    { QString::fromStdString(name) };

    QFile file(base_path + q_folder + q_name);

    file.copy(home_path + slash + q_name);

    if (!QFile::exists(home_path + slash + q_name))
    { std::cout << folder + name << " was not found.\n"; }

    assert(QFile::exists(home_path + slash + q_name));
}

void extract_file_vector(const std::string& folder,
                         const std::vector <std::string>& names)
{
    for (const std::string& name: names)
    { extract_file(folder, name); }
}

