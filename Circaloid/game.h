#ifndef GAME_H
#define GAME_H

#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

#include "SFML/Graphics.hpp"

#include "functions.h"
#include "tohoid.h"

class Game
{
    const int m_div;
    const float m_amount;

    std::vector <float> init_rotats();
    std::vector <sf::Vector2f> init_posits(const sf::Vector2f &windims,
                                           const std::vector<float> &rotats);

    std::vector <std::string> init_names();
    std::vector <std::vector <sf::Keyboard::Key>> init_keybindings();

    std::vector <Tohoid> init_tohoids(const sf::Vector2f &windims,
                                      const std::vector <sf::Vector2f> &posits,
                                      const std::vector <float> &rotats,
                                      const std::vector <std::string> &names,
                                      const std::vector <std::vector <sf::Keyboard::Key>> &keys, const float frame);

    void touhous_die(std::vector <Tohoid> &touhous);

    bool game_loop(sf::RenderWindow &window, const sf::Color &background, const sf::Vector2f &windims, std::vector<Tohoid> &touhous, const float frame);

public:

    explicit Game();
    ~Game();

    void run(sf::RenderWindow &window, const sf::Vector2f &windims, const sf::Color &background, const float frame, bool &nope);
};

std::vector <sf::Keyboard::Key> chars2keys(const std::vector <char> &charas);

#endif // GAME_H
