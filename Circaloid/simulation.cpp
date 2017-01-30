#include "simulation.h"

Simulation::Simulation()
    : m_winame("Circaloid"), m_windims(600.0f, 600.0f),
      m_window(sf::VideoMode(m_windims.x, m_windims.y), m_winame, sf::Style::Default),
      m_background(0, 0, 0), m_fps(60), m_frame(1.0f/static_cast<float>(m_fps))
{
    m_window.setVerticalSyncEnabled(true);

}

void Simulation::run()
{
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

        m_window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < m_frame)
        {
            time = clock.getElapsedTime();
        }
    }
}
