#include "todio.h"

Todio::Todio(const std::string& foldername,
             const std::string& filename,
             const bool loops)
    : m_folder_name(foldername),
      m_filename(filename),
      m_loops(loops),
      m_buffer(),
      m_sound()
{
    // rebuff();
}

void Todio::rebuff()
{
    assert(m_folder_name != "");
    assert(m_filename != "");

    if (m_folder_name != "" && m_filename != "")
    {       
        if (!m_buffer.loadFromFile(m_filename))
        { std::cerr << "Failed to load " << m_filename << "\n"; }

        m_sound.setBuffer(m_buffer);

        if (m_loops)
        { m_sound.setLoop(true); }

    }
}

void Todio::ring()
{ m_sound.play(); }

void Todio::stop()
{ m_sound.stop(); }
