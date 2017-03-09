#include "choice.h"

Choice::Choice()
    : m_chosen(false),
      m_amount(0),
      m_amount_names(),
      m_player_names(),
      m_player_textures(),
      m_player_sprites()
{
    m_amount_names.push_back("Zero_64.png");
    m_amount_names.push_back("One_64.png");
    m_amount_names.push_back("Two_64.png");
    m_amount_names.push_back("Three_64.png");
    m_amount_names.push_back("Four_64.png");

    m_player_names.push_back("Patchouli_64.png");
    m_player_names.push_back("Meiling_64.png");
    m_player_names.push_back("Sakuya_64.png");
    m_player_names.push_back("Keine_64.png");
}

Choice::~Choice()
{}

void Choice::choose(sf::RenderWindow &window)
{

}
