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
	struct TextManager : virtual public sf::Drawable
	{
		TextManager(const std::string& str = "", const sf::Vector2f& pos = { 0,0 });
		TextManager(const sf::Text& text, const sf::Vector2f& pos = { 0,0 });
		TextManager(const std::string& str, const std::string& fontPath, unsigned int charSize, const sf::Vector2f& pos = { 0,0 });
		TextManager(const TextManager& copy);

		void setString(const std::string& str);
		void setFont(const std::string& path);

		sf::Text text; ///< Text to display
		sf::Font font; ///< Font used to display the string

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}
#endif // _TEXT_MANAGER_HPP_