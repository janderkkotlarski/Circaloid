#include "todio.h"

Todio::Todio(std::vector<std::string>& names)
    : m_names(names),
      m_buffers(),
      m_sounds()
{
    for (const std::string& name : m_names)
    {
        assert(name != "");

        if (name != "")
        {
            sf::SoundBuffer buff;

            if (!buff.loadFromFile(name))
            { std::cerr << "Failed to load " << name << "\n"; }

            m_buffers.push_back(buff);
        }
    }
}


void Todio::ring()
{
    m_sounds.setBuffer(m_buffers[1]);
    // m_sounds.setLoop(true);

    m_sounds.play();
}

void Todio::stop()
{ m_sounds.stop(); }
