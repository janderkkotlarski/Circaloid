#include "menu.h"

Menu::Menu()
    : m_name("Danmakoid"),
      m_side(750.0f),
      m_background(0, 0, 0),
      m_window()
{

}

void Menu::start()
{
    int repeat{1};

    while (repeat != 0)
    {
        Game game;

        repeat = game.run();
    }
}
