#include "FrameRate.hpp"

namespace EngineSupport
{

	FrameRate::FrameRate(std::string path, sf::Color color) : Timer()
	{
		m_font.loadFromFile(path);
		m_text.setFillColor(color);
		m_text.setFont(m_font);
		m_text.setString("FPS: " + std::to_string(static_cast<int>(elapse())));
	}
	const sf::Text& FrameRate::getText(float x, float y, unsigned int charSize)
	{
		static sf::Clock clock;
		static auto temp = m_text;
		if (clock.getElapsedTime().asMilliseconds() % 30 == 0)
			temp.setString("FPS: " + std::to_string(static_cast<int>(elapse())));
		temp.setPosition(x, y);
		temp.setCharacterSize(charSize);
		return temp;
	}
	double FrameRate::elapse() const noexcept
	{
		double fpsLim = static_cast<double>(1 / std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count());
		return fpsLim;
	}
}