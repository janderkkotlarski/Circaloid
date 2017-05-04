#include "todio.h"

Todio::Todio(const std::vector<std::string> &names,
             const std::vector<bool>& loops)
    : m_names(names),
      m_loops(loops),
      m_buffers(),
      m_sounds()
{
    int count
    { 0 };
    assert(count == 0);

    for (const std::string& name : m_names)
    {
        assert(name != "");

        if (name != "")
        {
            sf::SoundBuffer buff;

            if (!buff.loadFromFile(name))
            { std::cerr << "Failed to load " << name << "\n"; }

            m_buffers.push_back(buff);

            sf::Sound sound;

            m_sounds.push_back(sound);
            m_sounds[count].setBuffer(m_buffers[count]);

            if (m_loops[count])
            { m_sounds[count].setLoop(true); }

        }

        ++count;
    }
}

void Todio::ring(const int here)
{ m_sounds[here].play(); }

void Todio::stop(const int here)
{ m_sounds[here].stop(); }
