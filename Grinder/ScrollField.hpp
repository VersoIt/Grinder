#pragma once
#ifndef _SCROLL_FIELD_HPP_
#define _SCROLL_FiELD_HPP_

#include <string>
#include "Button.hpp"

namespace EngineComponents
{
	class ScrollField : public Button
	{
	public:

		enum class Style
		{
			Default,
			Text
		};

		ScrollField(sf::Window& window, Button* button, Button* minButton, Button* maxButton, std::string imagePath, std::string hoverPath, sf::Vector2f pos);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos);

		virtual ~ScrollField();

	private:
		Button* m_button;
		sf::Window& m_window;
		bool m_isMove;

		Button* m_currentButton;
		Button* m_minButton;
		Button* m_maxButton;

		sf::Text m_shadowText;

		float m_dX;
	};
}

#endif // _SCROLL_FIELD_HPP_