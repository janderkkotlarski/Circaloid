#include "choice.h"

Choice::Choice()
    : m_chosen(false),
      m_amount(0),
      m_amount_names(),
      m_amount_texures(),
      m_amount_sprite(),
      m_player_names(),
      m_player_textures(),
      m_player_sprites()
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
                  std::vector <sf::Sprite> &sprites,
                  const sf::Vector2f &windims)
{
    assert(textures.size() > 0);

    sf::Sprite sprite;

    for(int count{0}; count < static_cast<int>(textures.size()); ++count)
    {
        sprites.push_back(sprite);

        set_sprite((0.07f + 0.07f*static_cast<float>(count))*windims, 0.0f, textures[count], sprites[count]);
    }

    assert(textures.size() == sprites.size());
}

void Choice::show_sprites(std::vector <sf::Sprite> &sprites,
                          sf::RenderWindow &window)
{
    assert(sprites.size() > 0);

    for(int count{0}; count < static_cast<int>(sprites.size()); ++count)
    {
        window.draw(sprites[count]);
    }
}

bool Choice::choose_loop(sf::RenderWindow &window, const sf::Color &background,
                         const float frame, const sf::Vector2f &windims)
{
    bool loop{true};

    const std::string filetatami{"Tatami.png"};
    sf::Texture textami;
    sf::Sprite spritami;

    set_image(filetatami, windims, textami, spritami);

    const std::string filename{"Frame.png"};
    sf::Texture texture;
    sf::Sprite sprite;

    set_image(filename, windims, texture, sprite);

    while(loop)
    {
        sf::Event event;
        sf::Clock clock;
        sf::Time time;

        if(polling(window, event, loop))
        {
            return true;
        }

        window.clear(background);
        window.draw(spritami);

        show_sprites(m_player_sprites, window);

        window.draw(m_amount_sprite);

        window.draw(sprite);
        window.display();

        time = clock.getElapsedTime();

        while(time.asSeconds() < frame)
        { time = clock.getElapsedTime(); }
    }

    return false;
}

void Choice::run(sf::RenderWindow &window, const sf::Vector2f &windims,
                 const sf::Color &background, const float frame,
                 bool &nope)
{
    init_textures(m_amount_names, m_amount_texures);

    set_sprite(0.0f*windims, 0.0f, m_amount_texures[0], m_amount_sprite);

    init_textures(m_player_names, m_player_textures);

    init_sprites(m_player_textures, m_player_sprites, windims);

    if (!nope)
    {
        nope = choose_loop(window, background, frame, windims);
    }
}
