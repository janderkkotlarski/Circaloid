#ifndef CHOICE_H
#define CHOICE_H

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "SFML/Graphics.hpp"

#include "functions.h"
#include "todio.h"

class Choice
{
    const sf::Vector2f m_windims;

    bool m_chosen;

    int m_amount;

    const std::string m_folder;

    std::vector <std::string> m_amount_names;
    std::vector <sf::Texture> m_amount_textures;
    sf::Sprite m_amount_sprite;

    std::vector <std::string> m_player_names;
    std::vector <sf::Texture> m_player_textures;
    std::vector <sf::Sprite> m_player_sprites;

    std::vector <bool> m_player_chosen;

public:

    explicit Choice(const sf::Vector2f& windims);
    ~Choice();

    void init_textures(std::vector <std::string>& names,
                       std::vector <sf::Texture>& textures);

    void init_sprites(std::vector <sf::Texture>& textures,
                      std::vector <sf::Sprite>& sprites);

    void show_sprites(sf::RenderWindow& window,
                      std::vector<bool>& player_chosen);

    void chara_click(sf::RenderWindow& window,
                     std::vector<std::string>& touhou_names,
                     std::vector <bool>& player_chosen,
                     std::vector <sf::Texture>& amount_textures,
                     sf::Sprite& amount_sprite,
                     int& amount);

    void amount_click(sf::RenderWindow& window,
                      bool& loop);

    bool choose_loop(sf::RenderWindow& window,
                     const sf::Color& background,
                     const float frame,
                     std::vector<std::string>& touhou_names);

    int run(sf::RenderWindow& window,
            const sf::Color& background,
            const float frame,
            bool& nope,
            std::vector<std::string>& touhou_names);
};

#endif // CHOICE_H
