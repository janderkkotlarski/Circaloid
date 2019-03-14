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

    std::string m_foldername;
    std::vector <std::string> m_filenames;
    std::vector <std::string> m_touhou_names;

    void list_files();
    void transfer_files();

public:

    explicit Menu();
    ~Menu();

    void start();
};

#endif // MENU_H
