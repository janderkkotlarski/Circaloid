#ifndef SIMULATION_H
#define SIMULATION_H

#include <cassert>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

class Simulation
{
    const std::string m_winame;
    const sf::Vector2f m_windims;

    sf::RenderWindow m_window;

    sf::View m_view;

    const sf::Color m_background;

    const int m_fps;
    const float m_frame;
    const int m_div;

public:

    Simulation();

    void run();
};

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas);

#endif // SIMULATION_H
