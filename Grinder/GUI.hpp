#pragma once
#ifndef _GUI_HPP_
#define _GUI_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <vector>
#include "Container.hpp"
#include "Manager.hpp"
#include "RenderObject.hpp"

namespace EngineComponents
{
	class GUI : public Container<RenderObject>, public RenderObject
	{
	public:

		GUI(const std::string& backgroundPath = "", const std::string& text = "", size_t capacity = 5);

		virtual void setSize(const sf::Vector2f& targetSize) override;
		virtual void setScale(const sf::Vector2f factors) override;

		virtual void setPosition(sf::Vector2f pos) override;
		virtual void setRotation(float degrees) override;

		virtual void move(sf::Vector2f offset) override;
		virtual void rotate(float degrees) override;

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}

#endif // _GUI_HPP_