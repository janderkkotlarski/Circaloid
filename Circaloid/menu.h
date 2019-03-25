#ifndef MENU_H
#define MENU_H

#include <cassert>
#include <string>

#include "choice.h"
#include "game.h"

class Menu
{
    const std::string m_name;
    const float m_side;
    sf::Color m_background;
    sf::RenderWindow m_window;

    const float m_fps;
    const float m_frame;

    std::vector <std::string> m_art_names;
    std::vector <std::string> m_number_names;
    std::vector <std::string> m_touhou_names;
    std::vector <std::string> m_chara_names;
    std::vector <std::string> m_projectile_names;
    std::vector <std::string> m_track_names;
    std::vector <std::string> m_sound_names;

    std::string m_foldername;
    std::vector <std::string> m_filenames;


    void list_files();
    void transfer_files();

public:

    explicit Menu();
    ~Menu();

    void start();
};

#endif // MENU_H
