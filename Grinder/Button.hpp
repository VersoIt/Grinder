#pragma once
#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <functional>
#include "SpriteManager.hpp"
#include "TextManager.hpp"
#include "MouseEventable.hpp"
#include "Manager.hpp"
#include "EventObject.hpp"

namespace EngineComponents
{
	class Button : public EventObject
	{
	public:

		Button(const std::string& imagePath, const std::string& hoverPath, std::function<void(void)> action = []() {}, const sf::Vector2f& pos = { 0, 0 }, const std::string& text = "");

		Button(sf::Vector2f increase, const std::string& imagePath, const std::string& hoverPath, std::function<void(void)> action = []() {}, const sf::Vector2f& pos = { 0, 0 }, const std::string& text = "");

		void setCurrentSprite(const SpriteManager& copySprite) { m_currentSprite = copySprite; }

		virtual void setScale(const sf::Vector2f factors) override;
		virtual void setSize(const sf::Vector2f& targetSize) override;

		virtual void setPosition(const sf::Vector2f& pos) override;
		virtual void setRotation(float degrees) override;

		virtual void move(sf::Vector2f offset) override;
		virtual void rotate(float degrees) override;

		SpriteManager& getCurrentSprite() { return m_currentSprite; }
		const SpriteManager& getCurrentSprite() const { return m_currentSprite; }

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override;

		SpriteManager& getHover() { return m_hover; }
		const SpriteManager& getHover() const { return m_hover; }

		std::function<void(void)>& getAction() { return m_action; }
		const std::function<void(void)>& getAction() const { return m_action; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		std::function<void(void)> m_action;
		SpriteManager m_hover;
		SpriteManager m_currentSprite;

		bool m_isClicked;
	};
}

#endif // _BUTTON_HPP_