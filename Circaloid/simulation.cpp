#include "simulation.h"
#include "circloid.h"

Simulation::Simulation()
    : m_winame("Circaloid"), m_windims(600.0f, 600.0f),
      m_window(sf::VideoMode(m_windims.x, m_windims.y), m_winame, sf::Style::Default),
      m_view(0.0f*m_windims, m_windims), m_background(0, 0, 0), m_fps(60), m_frame(1.0f/static_cast<float>(m_fps))
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

    Circloid circle{m_windims, 0.0f*m_windims, 0.01f*m_windims, 0.02f*m_windims.x, circolor, 100, m_frame};

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

        m_window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < m_frame)
        {
            time = clock.getElapsedTime();
        }
    }
}
