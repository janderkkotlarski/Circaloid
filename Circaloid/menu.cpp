#include "menu.h"

Menu::Menu()
    : m_name("Danmakoid"),
      m_side(750.0f),
      m_background(0, 0, 0),
      m_window(sf::VideoMode(static_cast<int>(m_side), static_cast<int>(m_side)), m_name, sf::Style::Default),
      m_fps(60.0f),
      m_frame(1/m_fps),
      m_foldername("/Circaloid/Resources/"),
      m_touhou_names()
{
    assert(m_name != "");
    assert(m_side > 0.0f);
    assert(m_background == sf::Color(0, 0, 0));
    assert(m_fps > 0.0f);
    assert(m_foldername != "");

    m_window.setVerticalSyncEnabled(true);
}

Menu::~Menu()
{}

void Menu::start()
{
    bool nope
    { false };
    assert(!nope);

    const sf::Vector2f windims
    { m_side, m_side };

    sf::View view(0.0f*windims, windims);
    m_window.setView(view);

    while (m_window.isOpen())
    {
        Choice choice(windims);

        const int amount
        { choice.run(m_window, m_background, m_frame, nope, m_foldername, m_touhou_names) };

        Game game;

        if (amount > 0)
        { game.run(m_window, windims, m_background, m_frame, amount, nope, m_foldername, m_touhou_names); }
    }
}
