#include "choice.h"

Choice::Choice(const sf::Vector2f& windims)
    : m_windims(windims),
      m_chosen(false),
      m_amount(0),
      m_folder("/Circaloid/Resources/"),
      m_amount_names(),
      m_amount_textures(),
      m_amount_sprite(),
      m_player_names(),
      m_player_textures(),
      m_player_sprites(),
      m_player_chosen()
{
    assert(windims.x > 0.0f);
    assert(windims.y > 0.0f);
    assert(!m_chosen);
    assert(m_amount == 0);
    assert(m_folder != "");

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
    { init_rotats(textures_size) };

    const std::vector <sf::Vector2f> posits
    { init_posits(0.5f*m_windims, rotats, textures_size) };

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
        { m_windims };

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
                { std::sqrt(vectralize(delta)) };

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
            0.5f*m_windims
        };

        const sf::Vector2f sprite_posit
        { m_amount_sprite.getPosition() };

        const sf::Vector2f delta
        { mouse_posit - sprite_posit };

        const float dist
        { std::sqrt(vectralize(delta)) };

        const float radius
        { sprite_radius(m_amount_sprite) };

        if (dist <= radius &&
            m_amount > 0)
        { loop = false; }
    }
}

bool Choice::choose_loop(sf::RenderWindow &window,
                         const sf::Color &background,
                         const float frame,
                         std::vector <std::string> &touhou_names)
{
    bool loop
    { true };
    assert(loop);

    const std::string filetatami
    { "Tatami.png" };
    assert(filetatami != "");

    extract_file(m_folder, filetatami);

    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, m_windims, textami, spritami);

    const std::string file_name
    { "Frame.png" };
    assert(file_name != "");

    extract_file(m_folder, file_name);

    sf::Texture texture;
    sf::Sprite sprite;

    set_image(file_name, m_windims, texture, sprite);

    while (loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if (polling(window, event, loop))
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

        window.clear(background);
        window.draw(spritami);

        show_sprites(window, m_player_chosen);

        window.draw(m_amount_sprite);

        window.draw(sprite);
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
                std::vector <std::string>& touhou_names)
{
    extract_file_vector(m_folder, m_amount_names);

    init_textures(m_amount_names, m_amount_textures);

    set_sprite(0.0f*m_windims, 0.0f, m_amount_textures[m_amount], m_amount_sprite);

    extract_file_vector(m_folder, m_player_names);

    init_textures(m_player_names, m_player_textures);
    init_sprites(m_player_textures, m_player_sprites);

    std::vector <std::string> sound_names
    ( { "Diur.wav", "Wuwr.wav" } );

    for (const std::string& sound_name : sound_names)
    {
        assert(sound_name != "");
    }

    extract_file_vector(m_folder, sound_names);

    Todio toadio(sound_names);

    toadio.ring();

    if (!nope)
    { nope = choose_loop(window, background, frame, touhou_names); }

    toadio.stop();

    return m_amount;
}
