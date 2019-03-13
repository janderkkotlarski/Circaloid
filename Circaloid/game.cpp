#include "game.h"

Game::Game()
    : m_div(100),
      m_amount(4),
      m_foldername()
{
    assert(m_div > 0);
    assert(m_amount > 0);
    assert(m_foldername == "");
}

Game::~Game()
{}

std::vector <std::vector <sf::Keyboard::Key>> Game::init_keybindings()
{
    const std::vector <char> charas_1
    { 'w', 's', 'd', 'a', 'q', 'e', 'x' };
    assert(charas_1.size() > 0);

    const std::vector <char> charas_2
    { 't', 'g', 'h', 'f', 'r', 'y', 'b' };
    assert(charas_1.size() == charas_2.size());

    const std::vector <char> charas_3
    { 'i', 'k', 'l', 'j', 'u', 'o', ',' };
    assert(charas_1.size() == charas_3.size());

    const std::vector <sf::Keyboard::Key> keyras_4
    {
        sf::Keyboard::Numpad8,
        sf::Keyboard::Numpad5,
        sf::Keyboard::Numpad6,
        sf::Keyboard::Numpad4,
        sf::Keyboard::Numpad7,
        sf::Keyboard::Numpad9,
        sf::Keyboard::Numpad2
    };

    assert(charas_1.size() == keyras_4.size());

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

void Game::touhous_die(std::vector <Tohoid>& touhous)
{
    assert(touhous.size() == static_cast<unsigned>(m_amount));

    for (Tohoid &touhou : touhous)
    {
        if ((touhou.get_quinergy() <= 0.0f) && touhou.is_alive())
        { touhou.dies(); }
    }
}

std::vector <Tohoid> Game::init_tohoids(const sf::Vector2f& windims,
                                        const std::vector <sf::Vector2f>& posits,
                                        const std::vector <float>& rotats,
                                        const std::string& foldername,
                                        const std::vector <std::string>& names,
                                        const std::vector <std::vector <sf::Keyboard::Key>>& keys,
                                        const float frame)
{
    std::vector <Tohoid> touhous;

    for (int count{0}; count < m_amount; ++count)
    {
        Tohoid touhou
        { windims, posits[count], rotats[count], foldername, names[count], frame, keys[count] };

        touhous.push_back(touhou);
    }

    assert(touhous.size() == static_cast<unsigned>(m_amount));

    for (Tohoid& touhou : touhous)
    { touhou.reimage(); }

    return touhous;
}

bool Game::game_loop(sf::RenderWindow& window,
                     const sf::Color& background,
                     const sf::Vector2f& windims,
                     std::vector <Tohoid>& touhous,
                     const float frame)
{
    bool loop
    { true };
    assert(loop);

    const std::string filetatami
    { "Dimensional_Grid.png" };
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, windims, textami, spritami);

    const std::string filename
    { "Dimensional_Chaos.png" };
    sf::Texture texture;
    sf::Sprite sprite;

    set_image(filename, windims, texture, sprite);

    for (Tohoid& touhou : touhous)
    { touhou.rebuff(); }

    while (loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if (polling(window, event, loop))
        { return true; }

        window.clear(background);
        window.draw(spritami);

        for (Tohoid& touhou : touhous)
        { touhou.display(window); }

        window.draw(sprite);
        window.display();

        for (Tohoid& touhou : touhous)
        { touhou.move(touhous); }

        touhous_die(touhous);

        time = clock.getElapsedTime();

        while(time.asSeconds() < frame)
        { time = clock.getElapsedTime(); }
    }

    return false;
}

void Game::run(sf::RenderWindow& window,
               const sf::Vector2f& windims,
               const sf::Color& background,
               const float frame,
               const int amount,
               bool& nope,
               const std::string& foldername,
               const std::vector <std::string>& touhou_names)
{
    assert(foldername != "");
    m_foldername = foldername;

    assert(frame > 0.0f);
    assert(amount > 0);
    m_amount = amount;

    const std::vector <float> rotats
    { init_rotats(m_amount) };

    const std::vector <sf::Vector2f> posits
    { init_posits(windims, rotats, m_amount) };

    const std::vector <std::vector <sf::Keyboard::Key>> keys
    { init_keybindings() };

    std::vector <Tohoid> touhous
    { init_tohoids(windims, posits, rotats, foldername, touhou_names, keys, frame) };

    if (!nope)
    { nope = game_loop(window, background, windims, touhous, frame); }
}

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char>& charas)
{
    assert(charas.size() > 0);
    const char aleph
    { 'a' };

    std::vector <sf::Keyboard::Key> keys;

    for (const char chara : charas)
    { keys.push_back(static_cast<sf::Keyboard::Key>(chara - aleph)); }

    assert(charas.size() == keys.size());
    return keys;
}
