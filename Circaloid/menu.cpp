#include "menu.h"

Menu::Menu()
    : m_name("Danmakoid"),
      m_side(750.0f),
      m_background(0, 0, 0),
      m_window(sf::VideoMode(m_side, m_side), m_name, sf::Style::Default)
{
    assert(m_name != "");
    assert(m_side > 0.0f);

    m_window.setVerticalSyncEnabled(true);
}

void Menu::start()
{
    const sf::Vector2f windims{m_side, m_side};

    sf::View view(0.0f*windims, windims);
    m_window.setView(view);

    while (m_window.isOpen())
    {
        Game game;

        game.run(m_window, windims, m_background);
    }
}
