#include "todio.h"

Todio::Todio(const std::string &name,
             const bool loops)
    : m_name(name),
      m_loops(loops),
      m_buffer(),
      m_sound()
{
    assert(m_name != "");

    if (m_name != "")
    {
        if (!m_buffer.loadFromFile(m_name))
        { std::cerr << "Failed to load " << m_name << "\n"; }

        m_sound.setBuffer(m_buffer);

        if (m_loops)
        { m_sound.setLoop(true); }

    }
}

void Todio::ring()
{ m_sound.play(); }

void Todio::stop()
{ m_sound.stop(); }
