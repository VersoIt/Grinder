#pragma once
#ifndef _FRAMERATE_HPP_
#define _FRAMERATE_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "Timer.hpp"

namespace EngineSupport
{
	class FrameRate : public Timer
	{
		sf::Text m_text;
		sf::Font m_font;

	public:
		FrameRate(std::string path = "Fonts/monaco.ttf", sf::Color color = sf::Color::Green);
		const sf::Text& getText(float x, float y, unsigned int charSize = 36);

		void setTextPosition(sf::Vector2f pos) { m_text.setPosition(pos); }
		sf::Vector2f getTextPosition() const noexcept { return m_text.getPosition(); }

		virtual double elapse() const noexcept override;

	};
}

#endif // _FRAMERATE_HPP_