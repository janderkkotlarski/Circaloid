#include "game.h"

Game::Game()
    : m_fps(60),
      m_frame(1.0f/static_cast<float>(m_fps)),
      m_div(100),
      m_loop(true)
{
    assert(m_fps > 0);
    assert(m_div > 0);
    assert(m_loop);
}

Game::~Game()
{
}

void Game::run(sf::RenderWindow &window, const sf::Vector2f &windims, const sf::Color &background)
{

    const int amount{3};

    const std::string patchy{"Patchouli_64.png"};
    assert(patchy != "");

    const std::string meily{"Meiling_64.png"};
    assert(meily != "");

    const std::string sakuy{"Sakuya_64.png"};
    assert(sakuy != "");

    std::vector <std::string> names;
    if (amount >= 1) {names.push_back(patchy);}
    if (amount >= 2) {names.push_back(meily);}
    if (amount >= 3) {names.push_back(sakuy);}

    assert(names.size() > 0);

    for (std::string name : names)
    {
        assert(name != "");
    }

    const std::vector <char> charas_1{'w', 's', 'd', 'a', 'x', 'z', 'q'};
    assert(charas_1.size() > 0);

    const std::vector <char> charas_2{'t', 'g', 'h', 'f', 'b', 'v', 'r'};
    assert(charas_1.size() == charas_2.size());

    const std::vector <char> charas_3{'i', 'k', 'l', 'j', 'm', 'n', 'u'};
    assert(charas_1.size() == charas_3.size());

    std::vector <std::vector <sf::Keyboard::Key>> keys;
    if (amount >= 1) {keys.push_back(chars2keys(charas_1));}
    if (amount >= 2) {keys.push_back(chars2keys(charas_2));}
    if (amount >= 3) {keys.push_back(chars2keys(charas_3));}

    assert(keys.size() > 0);

    std::vector <float> rotats;

    for (int count {0}; count < amount; ++count)
    {
        rotats.push_back(static_cast<float>(count)*360.0f/static_cast<float>(amount));
    }

    std::vector <sf::Vector2f> posits;

    for (int count {0}; count < amount; ++count)
    {
        posits.push_back(-0.7f*windims.x*rotation2direction(rotats[count]));
    }

    const sf::Vector2f speed{0.0f*windims};

    const float light{0.02f*windims.x};

    const float accel{0.00001f*windims.x};
    const float pheta{0.01f*M_PI};
    assert(pheta > 0.0f);    

    Tohoid patchouli{windims, posits[0], speed, light, accel, rotats[0], pheta, names[0], m_div, m_frame, keys[0]};
    Tohoid meiling{windims, posits[1], speed, light, accel, rotats[1], pheta, names[1], m_div, m_frame, keys[1]};
    Tohoid sakuya{windims, posits[2], speed, light, accel, rotats[2], pheta, names[2], m_div, m_frame, keys[2]};

    std::vector <Tohoid> touhous;
    if (amount >= 1) {touhous.push_back(patchouli);}
    if (amount >= 2) {touhous.push_back(meiling);}
    if (amount >= 3) {touhous.push_back(sakuya);}


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
                {
                    window.close();
                }

                m_loop = false;
            }
        }

        window.clear(background);

        window.draw(spritami);

        for (int count{0}; count < amount; ++count)
        {
            touhous[count].display(window);
        }

        window.draw(sprite);
        window.display();

        for (int count{0}; count < amount; ++count)
        {
            touhous[count].move(touhous);
        }

        touhous_die(touhous);

        time = clock.getElapsedTime();

        while(time.asSeconds() < m_frame)
        {
            time = clock.getElapsedTime();
        }
    }
}

void Game::touhous_die(std::vector <Tohoid> &touhous)
{
    for (int count{0}; count < static_cast<int>(touhous.size()); ++count)
    {
        if ((touhous[count].get_quinergy() <= 0.0f) && touhous[count].get_vivid())
        {
            touhous[count].dies();
        }
    }
}

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas)
{
    assert(charas.size() > 0);
    const char aleph{'a'};

    std::vector <sf::Keyboard::Key> keys;

    for (char chara : charas)
    {
        keys.push_back(static_cast<sf::Keyboard::Key>(chara - aleph));
    }

    return keys;
}

void set_image(const std::string &name, const sf::Vector2f &windims,
               sf::Texture &texture, sf::Sprite &sprite)
{
    assert(name != "");

    if (!texture.loadFromFile(name))
    {
        std::cerr << name << "not found!\n";
    }

    texture.setSmooth(true);

    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*windims);
    sprite.setPosition(0.0f*windims);
}
