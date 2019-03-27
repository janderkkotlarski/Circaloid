#include "choice.h"

Choice::Choice(const sf::Vector2f& window_dimensions)
    : m_window_dimensions(window_dimensions),
      m_chosen(false),
      m_amount(0),
      m_folder_name(""),
      m_amount_names(),
      m_amount_textures(),
      m_amount_sprite(),
      m_player_names(),
      m_player_textures(),
      m_player_sprites(),
      m_player_chosen()
{
    assert(window_dimensions.x > 0.0f);
    assert(window_dimensions.y > 0.0f);
    assert(!m_chosen);
    assert(m_amount == 0);
    assert(m_folder_name == "");

    m_amount_names.push_back("Zero_64.png");
    m_amount_names.push_back("One_64.png");
    m_amount_names.push_back("Two_64.png");
    m_amount_names.push_back("Three_64.png");
    m_amount_names.push_back("Four_64.png");

    assert(m_amount_names.size() == 5);

    for (const std::string& name : m_amount_names)
    { assert(name != ""); }

    m_player_names.push_back("Patchouli_64.png");
    m_player_names.push_back("Meiling_64.png");
    m_player_names.push_back("Sakuya_64.png");
    m_player_names.push_back("Keine_64.png");

    assert(m_player_names.size() == 4);

    for (const std::string& name : m_player_names)
    {
        assert(name != "");

        m_player_chosen.push_back(false);
    }
}

Choice::~Choice()
{}

void Choice::init_textures(std::vector<std::string>& names,
                           std::vector<sf::Texture>& textures)
{
    assert(names.size() > 0);

    int count
    { 0 };
    assert(count == 0);

    sf::Texture texture;

    for (const std::string& name : names)
    {
        assert(name != "");

        textures.push_back(texture);

        if (!textures[count].loadFromFile(name))
        { std::cerr << name << "not found!\n"; }

        ++count;
    }

    assert(names.size() == textures.size());
}

void Choice::init_sprites(std::vector <sf::Texture>& textures,
                          std::vector <sf::Sprite>& sprites)
{
    assert(textures.size() > 0);

    sf::Sprite sprite;

    const int textures_size
    { static_cast<int>(textures.size()) };

    const std::vector <float> rotats
    { initialize_rotations(textures_size) };

    const std::vector <sf::Vector2f> posits
    { initialize_positions(0.5f*m_window_dimensions, rotats, textures_size) };

    int count
    { 0 };
    assert(count == 0);

    for (const sf::Vector2f& posit : posits)
    {
        sprites.push_back(sprite);
        set_sprite(posit, 0.0f, textures[count], sprites[count]);

        ++count;
    }

    assert(textures.size() == sprites.size());
}

void Choice::show_sprites(sf::RenderWindow& window,
                          std::vector <bool>& player_chosen)
{
    int count
    { 0 };
    assert(count == 0);

    for(sf::Sprite& sprite : m_player_sprites)
    {
        if (!player_chosen[count])
        { window.draw(sprite); }

        ++count;
    }
}

void Choice::chara_click(sf::RenderWindow& window,
                         std::vector <std::string>& touhou_names,
                         std::vector <bool>& player_chosen,
                         std::vector<sf::Texture>& amount_textures,
                         sf::Sprite& amount_sprite,
                         int& amount)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        const sf::Vector2f windims
        { m_window_dimensions };

        const std::vector <std::string> player_names
        { m_player_names };

        const sf::Vector2f mouse_posit
        {
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) -
            0.5f*windims
        };

        int count
        { 0 };
        assert(count == 0);

        for (sf::Sprite& player_sprite : m_player_sprites)
        {
            if (!player_chosen[count])
            {
                const sf::Vector2f sprite_posit
                { player_sprite.getPosition() };

                const sf::Vector2f delta
                { mouse_posit - sprite_posit };

                const float dist
                { std::sqrt(squaring_vector(delta)) };

                const float radius
                { sprite_radius(player_sprite) };

                if (dist <= radius)
                {
                    player_chosen[count] = true;
                    ++amount;
                    set_sprite(0.0f*windims, 0.0f, amount_textures[amount], amount_sprite);
                    touhou_names.push_back(player_names[count]);
                }
            }

            ++count;
        }
    }
}

void Choice::amount_click(sf::RenderWindow& window,
                          bool& loop)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        const sf::Vector2f mouse_posit
        {
            static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) -
            0.5f*m_window_dimensions
        };

        const sf::Vector2f sprite_posit
        { m_amount_sprite.getPosition() };

        const sf::Vector2f delta
        { mouse_posit - sprite_posit };

        const float dist
        { std::sqrt(squaring_vector(delta)) };

        const float radius
        { sprite_radius(m_amount_sprite) };

        if (dist <= radius &&
            m_amount > 0)
        { loop = false; }
    }
}

bool Choice::choose_loop(sf::RenderWindow &window,
                         const sf::Color &background_color,
                         const float frame,
                         std::vector <std::string>& touhou_names)
{
    bool loop
    { true };
    assert(loop);

    const std::string background_file
    { "Dimensional_Grid.png" };
    assert(background_file != "");

    sf::Texture texture_background;
    sf::Sprite sprite_background;

    set_image(background_file, m_window_dimensions, texture_background, sprite_background);

    const std::string border_file
    { "Dimensional_Chaos.png" };
    assert(border_file != "");

    sf::Texture text_border;
    sf::Sprite sprite_border;

    set_image(border_file, m_window_dimensions, text_border, sprite_border);

    while (loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if (poll_reset_quit(window, event, loop))
        { return true; }
        else if (!loop)
        { m_amount = 0; }

        chara_click(window,
                    touhou_names,
                    m_player_chosen,
                    m_amount_textures,
                    m_amount_sprite,
                    m_amount);

        amount_click(window, loop);

        window.clear(background_color);
        window.draw(sprite_background);

        show_sprites(window, m_player_chosen);

        window.draw(m_amount_sprite);

        window.draw(sprite_border);
        window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < frame)
        { time = clock.getElapsedTime(); }
    }

    return false;
}

int Choice::run(sf::RenderWindow& window,
                const sf::Color& background,
                const float frame,
                bool& nope,
                const std::string& foldername,
                std::vector <std::string>& touhou_names)
{
    assert(foldername != "");
    m_folder_name = foldername;

    init_textures(m_amount_names, m_amount_textures);

    set_sprite(0.0f*m_window_dimensions, 0.0f, m_amount_textures[m_amount], m_amount_sprite);

    init_textures(m_player_names, m_player_textures);
    init_sprites(m_player_textures, m_player_sprites);

    std::vector <std::string> sound_names
    ( { "Diur.wav", "Bassoy.wav" } );

    std::vector <bool> sound_loops
    ( { false , false } );

    for (const std::string& sound_name : sound_names)
    {
        assert(sound_name != "");
    }

    const std::string menu_file
    { "Menu_Loop.ogg" };

    copy_file(m_folder_name, menu_file);

    sf::Music menu_music;

    if (!menu_music.openFromFile(menu_file))
    {
        nope = true;
        return -1;
    }

    menu_music.setLoop(true);

    menu_music.play();

       if (!nope)
    { nope = choose_loop(window, background, frame, touhou_names); }

    menu_music.stop();

    return m_amount;
}
