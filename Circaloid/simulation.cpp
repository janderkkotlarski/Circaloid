#include "simulation.h"


Simulation::Simulation()
    : m_winame("Circaloid"), m_windims(750.0f, 750.0f),
      m_window(sf::VideoMode(m_windims.x, m_windims.y), m_winame, sf::Style::Default),
      m_view(0.0f*m_windims, m_windims), m_background(0, 0, 0),
      m_fps(60), m_frame(1.0f/static_cast<float>(m_fps)), m_div(100)
{
    assert(m_winame != "");
    assert(m_windims.x > 0.0f);
    assert(m_windims.y > 0.0f);
    assert(m_fps > 0);

    m_window.setVerticalSyncEnabled(true);

    m_window.setView(m_view);
}

Simulation::~Simulation()
{
}

void Simulation::run()
{
    const std::vector <std::string> image_names{"Patchouli_64.png",
                                           "Meiling_64.png",
                                           "Sakuya_64.png"};

    assert(image_names.size() > 0);

    for (std::string name : image_names)
    {
        assert(name != "");
    }

    const std::vector <sf::Vector2f> posits{sf::Vector2f(0.0f*m_windims.x, -0.35f*m_windims.y),
                                           sf::Vector2f(0.3f*m_windims.x, 0.175f*m_windims.y),
                                           sf::Vector2f(-0.3f*m_windims.x, 0.175f*m_windims.y)};
    const sf::Vector2f speed{0.0f*m_windims.x, 0.0f*m_windims.y};

    const float light{0.02f*m_windims.x};

    const float accel{0.00001f*m_windims.x};
    const float pheta{0.01f*M_PI};
    assert(pheta > 0.0f);

    const std::vector <char> charas_1{'w', 's', 'd', 'a', 'x'};
    const std::vector <char> charas_2{'t', 'g', 'h', 'f', 'b'};
    const std::vector <char> charas_3{'i', 'k', 'l', 'j', 'm'};

    const std::vector <std::vector <sf::Keyboard::Key>> keys{chars2keys(charas_1),
                                                             chars2keys(charas_2),
                                                             chars2keys(charas_3)};

    Tohoid patchouli{m_windims, posits[0], speed, light, accel, pheta, image_names[0], m_div, m_frame, keys[0]};
    Tohoid meiling{m_windims, posits[1], speed, light, accel, pheta, image_names[1], m_div, m_frame, keys[1]};
    Tohoid sakuya{m_windims, posits[2], speed, light, accel, pheta, image_names[2], m_div, m_frame, keys[2]};

    std::vector <Tohoid> touhous{patchouli, meiling, sakuya};

    const int amount{static_cast<int>(touhous.size())};

    const std::string filetatami{"Tatami.png"};
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, m_windims, textami, spritami);

    const std::string filename{"Frame.png"};    
    sf::Texture texture;    
    sf::Sprite sprite;

    set_image(filename, m_windims, texture, sprite);

    while (m_window.isOpen())
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                m_window.close();
            }
        }

        m_window.clear(m_background);

        m_window.draw(spritami);

        for (int count{0}; count < amount; ++count)
        {
            touhous[count].display(m_window);
        }

        m_window.draw(sprite);
        m_window.display();

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

void Simulation::touhous_die(std::vector <Tohoid> &touhous)
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
