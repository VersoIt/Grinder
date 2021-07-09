#pragma once
#ifndef _TEXT_MANAGER_H_
#define _TEXT_MANAGER_H_

#include <SFML/Graphics.hpp>

namespace EngineComponents
{
	class TextManager : virtual public sf::Drawable
	{
	public:
		TextManager(const std::string& str = "");

		const sf::Text& getText() const { return m_text; }
		sf::Text& getText() { return m_text; }

		void setFont(const std::string& path);

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text m_text;
		sf::Font m_font;

	};
}
#endif // _TEXT_MANAGER_H_