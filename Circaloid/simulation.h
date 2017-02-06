#ifndef SIMULATION_H
#define SIMULATION_H

#include <cassert>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "tohoid.h"

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

    int return_type;

public:

    Simulation();

    ~Simulation();

    void touhous_die(std::vector <Tohoid> &touhous);

    int run();
};

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas);

void set_image(const std::string &name, const sf::Vector2f &windims,
               sf::Texture &texture, sf::Sprite &sprite);

#endif // SIMULATION_H
