#pragma once
#ifndef _EVENT_OBJECT_HPP_
#define _EVENT_OBJECT_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <string>
#include "MouseEventable.hpp"
#include "Object.hpp"

namespace EngineComponents
{
	class EventObject : public Object, public MouseEventable
	{

	public:
		EventObject(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text = "", const sf::Vector2f& pos = { 0,0 }) : Object(increase, backgroundPath, text, pos)
		{
		}

		EventObject(const std::string& backgroundPath, const std::string& text = "", const sf::Vector2f& pos = { 0,0 }) : Object(backgroundPath, text, pos)
		{
		}

		EventObject(const std::string& backgroundPath, const sf::Text& text) : Object(backgroundPath, text)
		{
		}

		EventObject(const std::string& backgroundPath, const TextManager& text) : Object (backgroundPath, text)
		{
		}

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override = 0;

		virtual ~EventObject() {};

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	};
}

#endif // _EVENT_OBJECT_HPP_