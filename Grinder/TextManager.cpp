#include "TextManager.hpp"

namespace EngineComponents
{
	TextManager::TextManager(const std::string& str) { m_text.setString(str); }

	TextManager::TextManager(const sf::Text& text) { m_text = text; }

	void TextManager::setFont(const std::string& path)
	{
		if (!m_font.loadFromFile(path))
			throw EngineComponents::FileMissing("The font file is missing.");
		m_text.setFont(m_font);
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	}

	void TextManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_text.getString() != "")
			target.draw(m_text, states);
	}

	void TextManager::setString(const std::string& str)
	{
		m_text.setString(str);
		m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	}
}