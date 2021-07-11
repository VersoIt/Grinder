#pragma once
#ifndef _GUI_OBJECT_HPP_
#define _GUI_OBJECT_HPP_

#include <SFML/Graphics.hpp>

#include "MouseEventable.hpp"
#include "Manager.hpp"
#include "SpriteManager.hpp"
#include "Object.hpp"
#include "TextManager.hpp"

namespace EngineComponents
{
	class RenderObject : public Object, public Manager, public SpriteManager, public TextManager
	{

	public:
		RenderObject(const std::string& backgroundPath, const std::string& text = "") : SpriteManager(backgroundPath), TextManager(text)
		{
		}

		RenderObject(const std::string& backgroundPath, const sf::Text& text) : SpriteManager(backgroundPath), TextManager(text)
		{
		}

		RenderObject(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text = "");

		virtual void setScale(const sf::Vector2f factors) override;
		virtual void setSize(const sf::Vector2f& targetSize) override;

		virtual void setPosition(sf::Vector2f pos) override;
		virtual void setRotation(float degrees) override;

		virtual void move(sf::Vector2f offset) override;
		virtual void rotate(float degrees) override;

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override {}

		virtual ~RenderObject() {};

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	};
}

#endif // _GUI_OBJECT_HPP_