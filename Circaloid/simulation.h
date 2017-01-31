#ifndef SIMULATION_H
#define SIMULATION_H

#include <cassert>
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

public:

    Simulation();

    void run();
};

#endif // SIMULATION_H
