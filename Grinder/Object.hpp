#pragma once
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <SFML/Graphics.hpp>

#include "MouseEventable.hpp"

namespace EngineComponents
{
	class Object : virtual public sf::Drawable, public EngineComponents::MouseEventable
	{
	public:
		Object()
		{
		}

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override = 0;

		std::string& getName() { return m_name; }
		const std::string& getName() const { return m_name; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	};
}

#endif // _OBJECT_HPP_