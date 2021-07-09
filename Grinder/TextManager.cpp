#include "TextManager.hpp"

namespace EngineComponents
{
	TextManager::TextManager(const std::string& str) { m_text.setString(str); }

	void TextManager::setFont(const std::string& path)
	{
		m_font.loadFromFile(path);
		m_text.setFont(m_font);
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	}

	void TextManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_text.getString() != "")
			target.draw(m_text, states);
	}
}