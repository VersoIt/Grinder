#pragma once
#ifndef _TEXT_MANAGER_HPP_
#define _TEXT_MANAGER_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "Exceptions.hpp"
#include <iostream>

namespace EngineComponents
{
	class TextManager : virtual public sf::Drawable
	{
	public:
		TextManager(const std::string& str = "", const sf::Vector2f& pos = { 0,0 });

		TextManager(const sf::Text& text, const sf::Vector2f& pos = { 0,0 });

		TextManager(const std::string& str, const std::string& fontPath, unsigned int charSize, const sf::Vector2f& pos = { 0,0 });

		TextManager(const TextManager& copy) : m_text{ copy.m_text }, m_font{ copy.m_font }
		{
			m_text.setFont(m_font);
		}

		void setString(const std::string& str);

		const sf::Text& getText() const { return m_text; }
		sf::Text& getText() { return m_text; }

		void setFont(const std::string& path);

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text m_text; ///< Text to display
		sf::Font m_font; ///< Font used to display the string

	};
}
#endif // _TEXT_MANAGER_HPP_