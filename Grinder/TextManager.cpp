#include "TextManager.hpp"

namespace EngineComponents
{
	TextManager::TextManager(const std::string& str, const sf::Vector2f& pos) 
	{ 
		text.setString(str);
		text.setPosition(pos);
	}

	TextManager::TextManager(const sf::Text& copyText, const sf::Vector2f& pos) : text{ copyText }
	{ 
		text.setPosition(pos);
	}

	TextManager::TextManager(const std::string& str, const std::string& fontPath, unsigned int charSize, const sf::Vector2f& pos)
	{
		text.setString(str);
		text.setCharacterSize(charSize);
		setFont(fontPath);
		text.setPosition(pos);
	}

	TextManager::TextManager(const TextManager& copy) : text{ copy.text }, font{ copy.font }
	{
		text.setFont(font);
	}

	void TextManager::setFont(const std::string& path)
	{
		if (!font.loadFromFile(path))
			throw EngineComponents::FileMissing("The font file is missing.");
		text.setFont(font);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	}

	void TextManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (text.getString() != "")
			target.draw(text, states);
	}

	void TextManager::setString(const std::string& str)
	{
		text.setString(str);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	}
}