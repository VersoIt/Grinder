#pragma once
#ifndef _SCROLL_FIELD_HPP_
#define _SCROLL_FiELD_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <string>
#include "Button.hpp"
#include "tinyxml2.h"

namespace EngineComponents
{
	class ScrollField : public Button
	{
	public:

		ScrollField(sf::Window& window, Button* button, Button* minButton, Button* maxButton, std::string imagePath, std::string hoverPath, const sf::Vector2f& pos, int share = 80);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos);

		int getShare() const { return m_share; }

		virtual ~ScrollField();

	private:

		Button* m_currentButton;
		sf::Window& m_window;
		bool m_isMove;

		Button* m_button;
		Button* m_minButton;
		Button* m_maxButton;

		sf::Text m_shadowText;

		int m_share;
		float m_dX;
	};
}

#endif // _SCROLL_FIELD_HPP_