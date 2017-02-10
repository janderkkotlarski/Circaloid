#ifndef MENU_H
#define MENU_H

#include <cassert>
#include <string>

#include "game.h"

class Menu
{
    std::string m_name;

    const float m_side;

    sf::Color m_background;

    sf::RenderWindow m_window;

public:

    Menu();

    void start();

};



#endif // MENU_H
