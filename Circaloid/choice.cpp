#include "choice.h"

Choice::Choice(const sf::Vector2f &windims)
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

void Choice::init_folder()
{
    QDir home_dir
    { QDir::current() };

    QString home_path
    { home_dir.absolutePath() };

    QDir base_dir
    { QDir::current() };

    base_dir.cdUp();

    QString base_path
    { base_dir.absolutePath() };

    QString q_folder
    { QString::fromStdString(m_folder) };

    std::cout << home_path.toStdString() << "\n";
    std::cout << base_path.toStdString() << "\n";

    // QDir::cdUp();

    QString slash
    { QString::fromStdString("/") };

    for (const std::string name: m_amount_names)
    {
      QString q_name
      { QString::fromStdString(name) };

      QFile file(base_path + q_folder + q_name);

      // extract.cd(home);

      file.copy(home_path + slash + q_name);

      if (!QFile::exists(home_path + slash + q_name))
      { std::cout << m_folder + name << " was not found.\n"; }

      assert(QFile::exists(home_path + q_name));
    }
}

void Choice::init_textures(std::vector<std::string> &names, std::vector<sf::Texture> &textures)
{
    assert(names.size() > 0);

    int count
    { 0 };

    sf::Texture texture;

    /*
    for(int count{0}; count < static_cast<int>(names.size()); ++count)
    {
        assert(names[count] != "");

        textures.push_back(texture);

        if (!textures[count].loadFromFile(names[count]))
        { std::cerr << names[count] << "not found!\n"; }
    }
    */

    std::for_each(std::begin(names),
                  std::end(names),
                  [&textures, texture, &count](const std::string &name)
                  {
                      assert(name != "");

                      textures.push_back(texture);

                      if (!textures[count].loadFromFile(name))
                      { std::cerr << name << "not found!\n"; }

                      ++count;
                  });

    // std::cout << textures.size() << "\n";

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

void Choice::show_sprites(sf::RenderWindow &window,
                          std::vector <bool> &player_chosen)
{
    int count
    { 0 };

    /*
    for (int count{0}; count < static_cast<int>(m_player_sprites.size()); ++count)
    {
        if (!m_player_chosen[count])
        { window.draw(m_player_sprites[count]); }
    }
    */

    for_each(std::begin(m_player_sprites),
             std::end(m_player_sprites),
             [&window, &player_chosen, &count](sf::Sprite &sprite)
             {
                if (!player_chosen[count])
                { window.draw(sprite); }

                ++count;
             });

}

void Choice::chara_click(sf::RenderWindow &window,
                         std::vector <std::string> &touhou_names,
                         std::vector <bool> &player_chosen,
                         std::vector<sf::Texture> &amount_textures,
                         sf::Sprite &amount_sprite,
                         int &amount)
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

        std::for_each(std::begin(m_player_sprites),
                      std::end(m_player_sprites),
                      [&window, &touhou_names, player_names, &player_chosen,
                       &amount_textures, &amount_sprite, windims,
                       &amount, mouse_posit, &count]
                      (sf::Sprite player_sprite)
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
                      });


        /*
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
                    set_sprite(0.0f*m_windims, 0.0f, m_amount_textures[m_amount], m_amount_sprite);
                    touhou_names.push_back(m_player_names[count]);
                }
            }
        }
        */

    }
}

void Choice::amount_click(sf::RenderWindow &window, bool &loop)
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

bool Choice::choose_loop(sf::RenderWindow &window, const sf::Color &background,
                         const float frame, std::vector <std::string> &touhou_names)
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

int Choice::run(sf::RenderWindow &window, const sf::Color &background,
                const float frame, bool &nope, std::vector <std::string> &touhou_names)
{
    init_folder();

    init_textures(m_amount_names, m_amount_textures);

    set_sprite(0.0f*m_windims, 0.0f, m_amount_textures[m_amount], m_amount_sprite);

    init_textures(m_player_names, m_player_textures);
    init_sprites(m_player_textures, m_player_sprites);

    std::vector <std::string> names
    ( { "Diur.wav", "Wuwr.wav" } );

    Todio toadio(names);

    toadio.ring();

    if (!nope)
    { nope = choose_loop(window, background, frame, touhou_names); }

    toadio.stop();

    return m_amount;
}
