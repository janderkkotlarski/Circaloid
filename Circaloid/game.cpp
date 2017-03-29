#include "game.h"

Game::Game()
    : m_div(100),
      m_amount(4)
{
    assert(m_div > 0);
    assert(m_amount > 0);
}

Game::~Game()
{}

std::vector <std::vector <sf::Keyboard::Key>> Game::init_keybindings()
{
     const std::vector <char> charas_1{'w', 's', 'd', 'a', 'x', 'z', 'q'};
     assert(charas_1.size() > 0);
     const std::vector <char> charas_2{'t', 'g', 'h', 'f', 'b', 'v', 'r'};
     assert(charas_1.size() == charas_2.size());
     const std::vector <char> charas_3{'i', 'k', 'l', 'j', 'm', 'n', 'u'};
     assert(charas_1.size() == charas_3.size());

     const std::vector <sf::Keyboard::Key> keyras_4
     {
        sf::Keyboard::Numpad8,
        sf::Keyboard::Numpad5,
        sf::Keyboard::Numpad6,
        sf::Keyboard::Numpad4,
        sf::Keyboard::Numpad2,
        sf::Keyboard::Numpad1,
        sf::Keyboard::Numpad7
     };

     std::vector <std::vector <sf::Keyboard::Key>> keys;
     if (m_amount >= 1)
     { keys.push_back(chars2keys(charas_1)); }
     if (m_amount >= 2)
     { keys.push_back(chars2keys(charas_2)); }
     if (m_amount >= 3)
     { keys.push_back(chars2keys(charas_3)); }
     if (m_amount >= 4)
     { keys.push_back(keyras_4); }

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
                                  const std::vector <std::vector <sf::Keyboard::Key>> &keys,
                                  const float frame)
{
    std::vector <Tohoid> touhous;

    if (m_amount >= 1)
    {
        Tohoid patchouli{windims, posits[0], rotats[0], names[0], frame, keys[0]};
        touhous.push_back(patchouli);
    }
    if (m_amount >= 2)
    {
        Tohoid meiling{windims, posits[1], rotats[1], names[1], frame, keys[1]};
        touhous.push_back(meiling);
    }
    if (m_amount >= 3)
    {
        Tohoid sakuya{windims, posits[2], rotats[2], names[2], frame, keys[2]};
        touhous.push_back(sakuya);
    }
    if (m_amount >= 4)
    {
        Tohoid keine{windims, posits[3], rotats[3], names[3], frame, keys[3]};
        touhous.push_back(keine);
    }

    assert(touhous.size() == static_cast<unsigned>(m_amount));

    for (int count{0}; count < m_amount; ++count)
    {
        touhous[count].reimage();
    }

    return touhous;
}

bool Game::game_loop(sf::RenderWindow &window, const sf::Color &background,
                     const sf::Vector2f &windims, std::vector <Tohoid> &touhous,
                     const float frame)
{
    bool loop{true};

    const std::string filetatami{"Tatami.png"};
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, windims, textami, spritami);

    const std::string filename{"Frame.png"};
    sf::Texture texture;
    sf::Sprite sprite;

    set_image(filename, windims, texture, sprite);

    while (loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if (polling(window, event, loop))
        {
            return true;
        }

        window.clear(background);
        window.draw(spritami);

        /*
        for (int count{0}; count < m_amount; ++count)
        { touhous[count].display(window); }
        */

        std::for_each(std::begin(touhous),
                      std::end(touhous),
                      [&window](Tohoid &touhou)
                      { touhou.display(window); });

        window.draw(sprite);
        window.display();

        /*
        for (int count{0}; count < m_amount; ++count)
        { touhous[count].move(touhous); }
        */

        std::for_each(std::begin(touhous),
                      std::end(touhous),
                      [&window, &touhous](Tohoid &touhou)
                      { touhou.move(touhous); });

        touhous_die(touhous);

        time = clock.getElapsedTime();

        while(time.asSeconds() < frame)
        { time = clock.getElapsedTime(); }
    }

    return false;
}

void Game::run(sf::RenderWindow &window, const sf::Vector2f &windims,
               const sf::Color &background, const float frame,
               const int amount, bool &nope, const std::vector <std::string> &touhou_names)
{
    assert(amount > 0);
    m_amount = amount;

    const std::vector <float> rotats
    { init_rotats(m_amount) };

    const std::vector <sf::Vector2f> posits
    { init_posits(windims, rotats, m_amount) };

    // const std::vector <std::string> names
    // { init_names() };

    const std::vector <std::vector <sf::Keyboard::Key>> keys
    { init_keybindings() };

    std::vector <Tohoid> touhous
    { init_tohoids(windims, posits, rotats, touhou_names, keys, frame) };

    if (!nope)
    { nope = game_loop(window, background, windims, touhous, frame); }
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
