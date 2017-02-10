#ifndef GAME_H
#define GAME_H

#include <cassert>
#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "functions.h"
#include "tohoid.h"

class Game
{
    const int m_fps;
    const float m_frame;
    const int m_div;
    bool m_loop;

public:

    explicit Game();

    ~Game();

    void touhous_die(std::vector <Tohoid> &touhous);

    void run(sf::RenderWindow &window, const sf::Vector2f &windims, const sf::Color &background);
};

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas);

void set_image(const std::string &name, const sf::Vector2f &windims,
               sf::Texture &texture, sf::Sprite &sprite);

#endif // GAME_H
