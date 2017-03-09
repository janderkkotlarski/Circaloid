#ifndef CHOICE_H
#define CHOICE_H

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"

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

    void choose(sf::RenderWindow &window);

};

#endif // CHOICE_H
