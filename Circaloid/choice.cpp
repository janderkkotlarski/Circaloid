#include "choice.h"

Choice::Choice(const sf::Vector2f &windims)
    : m_windims(windims),
      m_chosen(false),
      m_amount(0),
      m_amount_names(),
      m_amount_texures(),
      m_amount_sprite(),
      m_player_names(),
      m_player_textures(),
      m_player_sprites(),
      m_player_chosen(),
      m_names_chosen()
{
    m_amount_names.push_back("Zero_64.png");
    m_amount_names.push_back("One_64.png");
    m_amount_names.push_back("Two_64.png");
    m_amount_names.push_back("Three_64.png");
    m_amount_names.push_back("Four_64.png");

    assert(m_amount_names.size() == 5);

    m_player_names.push_back("Patchouli_64.png");
    m_player_names.push_back("Meiling_64.png");
    m_player_names.push_back("Sakuya_64.png");
    m_player_names.push_back("Keine_64.png");

    assert(m_player_names.size() == 4);

    for (int count{0}; count < static_cast<int>(m_player_names.size()); ++count)
    { m_player_chosen.push_back(false); }
}

Choice::~Choice()
{}

void Choice::init_textures(std::vector<std::string> &names, std::vector<sf::Texture> &textures)
{
    assert(names.size() > 0);

    sf::Texture texture;

    for(int count{0}; count < static_cast<int>(names.size()); ++count)
    {
        assert(names[count] != "");

        textures.push_back(texture);

        if (!textures[count].loadFromFile(names[count]))
        { std::cerr << names[count] << "not found!\n"; }
    }


    assert(names.size() == textures.size());
}

void Choice::init_sprites(std::vector <sf::Texture> &textures,
                  std::vector <sf::Sprite> &sprites)
{
    assert(textures.size() > 0);

    sf::Sprite sprite;

    const int textures_size = static_cast<int>(textures.size());

    const std::vector <float> rotats
    { init_rotats(textures_size) };

    const std::vector <sf::Vector2f> posits
    { init_posits(0.5f*m_windims, rotats, textures_size) };


    for (int count{0}; count < textures_size; ++count)
    {
        sprites.push_back(sprite);

        set_sprite(posits[count], 0.0f, textures[count], sprites[count]);
    }

    assert(textures.size() == sprites.size());
}

void Choice::show_sprites(sf::RenderWindow &window)
{
    for (int count{0}; count < static_cast<int>(m_player_sprites.size()); ++count)
    {
        if (!m_player_chosen[count])
        { window.draw(m_player_sprites[count]); }
    }

    /*
    for_each(std::begin(m_player_sprites),
             std::end(m_player_sprites),
             [&window](sf::Sprite &sprite)
             {
                window.draw(sprite);
             });
    */
}

void Choice::chara_click(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        const sf::Vector2f mouse_posit
        {
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) -
            0.5f*m_windims
        };

        for (int count{0}; count < static_cast<int>(m_player_sprites.size()); ++count)
        {
            if (!m_player_chosen[count])
            {
                const sf::Vector2f sprite_posit
                { m_player_sprites[count].getPosition() };

                const sf::Vector2f delta
                { mouse_posit - sprite_posit };

                const float dist
                { std::sqrt(vectralize(delta)) };

                 const float radius
                { sprite_radius(m_player_sprites[count]) };

                if (dist <= radius)
                {
                    m_player_chosen[count] = true;
                    ++m_amount;
                }
            }
        }
    }
}

bool Choice::choose_loop(sf::RenderWindow &window, const sf::Color &background,
                         const float frame)
{
    bool loop
    { true };

    const std::string filetatami
    { "Tatami.png" };
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, m_windims, textami, spritami);

    const std::string filename
    { "Frame.png" };
    sf::Texture texture;
    sf::Sprite sprite;

    set_image(filename, m_windims, texture, sprite);

    while (loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if (polling(window, event, loop))
        {
            return true;
        }

        chara_click(window);

        window.clear(background);
        window.draw(spritami);

        show_sprites(window);

        window.draw(m_amount_sprite);

        window.draw(sprite);
        window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < frame)
        { time = clock.getElapsedTime(); }
    }

    return false;
}

int Choice::run(sf::RenderWindow &window, const sf::Color &background,
                const float frame, bool &nope)
{
    init_textures(m_amount_names, m_amount_texures);

    set_sprite(0.0f*m_windims, 0.0f, m_amount_texures[0], m_amount_sprite);

    init_textures(m_player_names, m_player_textures);

    init_sprites(m_player_textures, m_player_sprites);

    if (!nope)
    {
        nope = choose_loop(window, background, frame);
    }

    return 4; //m_amount;
}
