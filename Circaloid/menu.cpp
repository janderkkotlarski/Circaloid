#include "menu.h"

Menu::Menu()
    : m_name("Danmakoid"),
      m_side(750.0f),
      m_background(0, 0, 0),
      m_window(sf::VideoMode(static_cast<int>(m_side), static_cast<int>(m_side)), m_name, sf::Style::Default),
      m_fps(60.0f),
      m_frame(1/m_fps),
      m_art_names(),
      m_number_names(),
      m_touhou_names(),
      m_chara_names(),
      m_projectile_names(),
      m_track_names(),
      m_sound_names(),
      m_folder_name("/Circaloid/Resources/"),
      m_filenames()

{
    assert(m_name != "");
    assert(m_side > 0.0f);
    assert(m_background == sf::Color(0, 0, 0));
    assert(m_fps > 0.0f);
    assert(m_folder_name != "");

    list_files();
    transfer_files();

    m_window.setVerticalSyncEnabled(true);
}

Menu::~Menu()
{}

void Menu::list_files()
{
    m_art_names.push_back("Dimensional_Chaos.png");
    m_art_names.push_back("Dimensional_Grid.png");

    m_filenames.insert(m_filenames.end(), m_art_names.begin(), m_art_names.end());

    m_number_names.push_back("Zero_64.png");
    m_number_names.push_back("One_64.png");
    m_number_names.push_back("Two_64.png");
    m_number_names.push_back("Three_64.png");
    m_number_names.push_back("Four_64.png");

    m_filenames.insert(m_filenames.end(), m_number_names.begin(), m_number_names.end());

    m_touhou_names.push_back("Keine_64.png");
    m_touhou_names.push_back("Meiling_64.png");
    m_touhou_names.push_back("Patchouli_64.png");
    m_touhou_names.push_back("Sakuya_64.png");

    m_filenames.insert(m_filenames.end(), m_touhou_names.begin(), m_touhou_names.end());

    m_chara_names.push_back("Direction_64.png");

    m_filenames.insert(m_filenames.end(), m_chara_names.begin(), m_chara_names.end());

    m_projectile_names.push_back("Star_128.png");

    m_filenames.insert(m_filenames.end(), m_projectile_names.begin(), m_projectile_names.end());

    m_track_names.push_back("Menu_Loop.ogg");

    m_filenames.insert(m_filenames.end(), m_track_names.begin(), m_track_names.end());

    m_sound_names.push_back("Single_Shot.wav");
    m_sound_names.push_back("Danmaku_Shot.wav");

    m_filenames.insert(m_filenames.end(), m_sound_names.begin(), m_sound_names.end());

}

void Menu::transfer_files()
{
    copy_file_vector(m_folder_name, m_filenames);
}

void Menu::start()
{
    bool nope
    { false };
    assert(!nope);

    const sf::Vector2f windims
    { m_side, m_side };

    sf::View view(0.0f*windims, windims);
    m_window.setView(view);

    while (m_window.isOpen())
    {
        Choice choice(windims);

        const int amount
        { choice.run(m_window, m_background, m_frame, nope, m_folder_name, m_touhou_names) };

        Game game;

        if (amount > 0)
        { game.run(m_window, windims, m_background, m_frame, amount, nope, m_folder_name, m_touhou_names); }
    }
}
