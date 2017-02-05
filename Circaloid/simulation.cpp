#include "simulation.h"
#include "circloid.h"

Simulation::Simulation()
    : m_winame("Circaloid"), m_windims(600.0f, 600.0f),
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

void Simulation::run()
{
    const sf::Color circolor{127, 127, 63};

    const sf::Vector2f posit{0.0f*m_windims};
    const sf::Vector2f speed{0.0f*m_windims.x, 0.0f*m_windims.y};

    const float light{0.02f*m_windims.x};

    const float accel{0.00001f*m_windims.x};
    const float pheta{0.01f*M_PI};

    const float radius{0.02f*m_windims.x};

    const int points{3};

    const std::vector <char> charas{'w', 's', 'd', 'a'};

    const std::vector <sf::Keyboard::Key> keys{chars2keys(charas)};

    const std::string filename{"Frame.png"};

    sf::Texture texture;

    if (!texture.loadFromFile(filename))
    {
        std::cerr << "Failed to load " << filename << "\n";
    }

    texture.setSmooth(true);

    sf::Sprite sprite;

    sprite.setTexture(texture);
    sprite.setOrigin(0.5f*m_windims);
    sprite.setPosition(0.0f*m_windims);

    Circloid circle{m_windims, posit, speed, light, accel, pheta, radius, points, circolor, m_div, m_frame, keys};

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

        circle.move();

        circle.display(m_window);

        m_window.draw(sprite);

        m_window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < m_frame)
        {
            time = clock.getElapsedTime();
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
