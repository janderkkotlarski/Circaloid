#ifndef CHOICE_H
#define CHOICE_H

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

#include "functions.h"

class Choice
{
    bool m_chosen;

    int m_amount;

    std::vector <std::string> m_amount_names;
    std::vector <sf::Texture> m_amount_texures;
    sf::Sprite m_amount_sprite;

    std::vector <std::string> m_player_names;
    std::vector <sf::Texture> m_player_textures;
    std::vector <sf::Sprite> m_player_sprites;

public:

    explicit Choice();
    ~Choice();

    void init_textures(std::vector <std::string> &names,
                       std::vector <sf::Texture> &textures);

    void init_sprites(std::vector <sf::Texture> &textures,
                      std::vector <sf::Sprite> &sprites,
                      const sf::Vector2f &windims);

    void show_sprites(std::vector <sf::Sprite> &sprites,
                      sf::RenderWindow &window);

    bool choose_loop(sf::RenderWindow &window, const sf::Color &background,
                     const float frame, const sf::Vector2f &windims);

    int run(sf::RenderWindow &window, const sf::Vector2f &windims,
             const sf::Color &background, const float frame,
             bool &nope);

};

#endif // CHOICE_H
