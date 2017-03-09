#include "game.h"

Game::Game()
    : m_fps(60),
      m_frame(1.0f/static_cast<float>(m_fps)),
      m_div(100),
      m_loop(true),
      m_amount(1)
{
    assert(m_fps > 0);
    assert(m_div > 0);
    assert(m_loop);
    assert(m_amount > 0);
}

Game::~Game()
{}

std::vector <float> Game::init_rotats()
{
    std::vector <float> rotats;

    for (int count {0}; count < m_amount; ++count)
    { rotats.push_back(static_cast<float>(count)*360.0f/static_cast<float>(m_amount)); }

    assert(rotats.size() == static_cast<unsigned>(m_amount));
    return rotats;
}

std::vector <sf::Vector2f> Game::init_posits(const sf::Vector2f &windims,
                                             const std::vector <float> &rotats)
{
    std::vector <sf::Vector2f> posits;

    for (int count {0}; count < m_amount; ++count)
    { posits.push_back(-0.7f*windims.x*rotation2direction(rotats[count])); }

    assert(posits.size() == static_cast<unsigned>(m_amount));
    return posits;
}

std::vector <std::string> Game::init_names()
{
    const std::string patchy{"Patchouli_64.png"};
    assert(patchy != "");
    const std::string meily{"Meiling_64.png"};
    assert(meily != "");
    const std::string sakuy{"Sakuya_64.png"};
    assert(sakuy != "");

    std::vector <std::string> names;
    if (m_amount >= 1)
    { names.push_back(patchy); }
    if (m_amount >= 2)
    { names.push_back(meily); }
    if (m_amount >= 3)
    { names.push_back(sakuy); }

    assert(names.size() == static_cast<unsigned>(m_amount));

    for (std::string name : names)
    { assert(name != ""); }

    return names;
}

std::vector <std::vector <sf::Keyboard::Key>> Game::init_keybindings()
{
     const std::vector <char> charas_1{'w', 's', 'd', 'a', 'x', 'z', 'q'};
     assert(charas_1.size() > 0);
     const std::vector <char> charas_2{'t', 'g', 'h', 'f', 'b', 'v', 'r'};
     assert(charas_1.size() == charas_2.size());
     const std::vector <char> charas_3{'i', 'k', 'l', 'j', 'm', 'n', 'u'};
     assert(charas_1.size() == charas_3.size());

     std::vector <std::vector <sf::Keyboard::Key>> keys;
     if (m_amount >= 1)
     { keys.push_back(chars2keys(charas_1)); }
     if (m_amount >= 2)
     { keys.push_back(chars2keys(charas_2)); }
     if (m_amount >= 3)
     { keys.push_back(chars2keys(charas_3)); }

     assert(keys.size() == static_cast<unsigned>(m_amount));
     return keys;
}

void Game::touhous_die(std::vector <Tohoid> &touhous)
{
    assert(touhous.size() == static_cast<unsigned>(m_amount));

    for (int count{0}; count < m_amount; ++count)
    {
        if ((touhous[count].get_quinergy() <= 0.0f) && touhous[count].get_vivid())
        { touhous[count].dies(); }
    }
}

std::vector <Tohoid> Game::init_tohoids(const sf::Vector2f &windims,
                                  const std::vector <sf::Vector2f> &posits,
                                  const std::vector <float> &rotats,
                                  const std::vector <std::string> &names,
                                  const std::vector <std::vector <sf::Keyboard::Key>> &keys)
{
    std::vector <Tohoid> touhous;
    if (m_amount >= 1)
    {
        Tohoid patchouli{windims, posits[0], rotats[0], names[0], m_frame, keys[0]};
        touhous.push_back(patchouli);
    }
    if (m_amount >= 2)
    {
        Tohoid meiling{windims, posits[1], rotats[1], names[1], m_frame, keys[1]};
        touhous.push_back(meiling);
    }
    if (m_amount >= 3)
    {
        Tohoid sakuya{windims, posits[2], rotats[2], names[2], m_frame, keys[2]};
        touhous.push_back(sakuya);
    }

    assert(touhous.size() == static_cast<unsigned>(m_amount));

    for (int count{0}; count < m_amount; ++count)
    {
        touhous[count].reimage();
    }

    return touhous;
}

void Game::game_loop(sf::RenderWindow &window, const sf::Color &background,
                     const sf::Vector2f &windims, std::vector <Tohoid> &touhous)
{
    const std::string filetatami{"Tatami.png"};
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, windims, textami, spritami);

    const std::string filename{"Frame.png"};
    sf::Texture texture;
    sf::Sprite sprite;

    set_image(filename, windims, texture, sprite);

    while (m_loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            {
                if (event.type == sf::Event::Closed ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                { window.close(); }

                m_loop = false;
            }
        }

        window.clear(background);
        window.draw(spritami);

        for (int count{0}; count < m_amount; ++count)
        { touhous[count].display(window); }

        window.draw(sprite);
        window.display();

        for (int count{0}; count < m_amount; ++count)
        { touhous[count].move(touhous); }

        touhous_die(touhous);

        time = clock.getElapsedTime();

        while(time.asSeconds() < m_frame)
        { time = clock.getElapsedTime(); }
    }
}

void Game::run(sf::RenderWindow &window, const sf::Vector2f &windims, const sf::Color &background)
{
    const std::vector <float> rotats
    { init_rotats() };

    const std::vector <sf::Vector2f> posits
    { init_posits(windims, rotats) };

    const std::vector <std::string> names
    { init_names() };

    const std::vector <std::vector <sf::Keyboard::Key>> keys
    { init_keybindings() };



    std::vector <Tohoid> touhous
    { init_tohoids(windims, posits, rotats, names, keys) };



    game_loop(window, background, windims, touhous);
}

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas)
{
    assert(charas.size() > 0);
    const char aleph{'a'};

    std::vector <sf::Keyboard::Key> keys;

    for (char chara : charas)
    { keys.push_back(static_cast<sf::Keyboard::Key>(chara - aleph)); }

    assert(charas.size() == keys.size());
    return keys;
}

void set_image(const std::string &name, const sf::Vector2f &windims,
               sf::Texture &texture, sf::Sprite &sprite)
{
    assert(name != "");

    if (!texture.loadFromFile(name))
    { std::cerr << name << "not found!\n"; }

    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*windims);
    sprite.setPosition(0.0f*windims);
}
