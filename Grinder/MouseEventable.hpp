#pragma once
#ifndef _EVENT_HPP_
#define _EVENT_HPP_

#include <SFML/Graphics.hpp>

namespace EngineComponents
{
	class MouseEventable
	{
	public:
		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) = 0;
	};
}

#endif // _EVENT_HPP_