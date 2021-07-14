#pragma once
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <string>
#include "MouseEventable.hpp"
#include "Manager.hpp"
#include "SpriteManager.hpp"
#include "TextManager.hpp"

namespace EngineComponents
{
	class Object : virtual public sf::Drawable, public Manager, public SpriteManager, public TextManager
	{
	public:
		Object() {};

		Object(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text, const sf::Vector2f& pos);

		Object(const std::string& backgroundPath, const std::string& text = "", const sf::Vector2f& pos = { 0,0 });

		Object(const std::string& backgroundPath, const sf::Text& text);

		Object(const std::string& backgroundPath, const EngineComponents::TextManager& text);

		virtual void setScale(const sf::Vector2f factors) override;
		virtual void setSize(const sf::Vector2f& targetSize) override;

		virtual void setPosition(const sf::Vector2f& pos) override;
		virtual void setRotation(float degrees) override;

		virtual void move(sf::Vector2f offset) override;
		virtual void rotate(float degrees) override;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif // _OBJECT_HPP_