#pragma once
#ifndef _GUI_HPP_
#define _GUI_HPP_

#include <vector>

#include "Container.hpp"
#include "Manager.hpp"
#include "GUIObject.hpp"

namespace EngineComponents
{
	class GUI : public Container<GUIObject>, public GUIObject, public Manager
	{
	public:

		GUI(const std::string& backgroundPath = "", size_t capacity = 5);

		virtual void setSize(const sf::Vector2f& targetSize) override;
		virtual void setScale(const sf::Vector2f factors) override;

		virtual void setPosition(sf::Vector2f pos) override;
		virtual void setRotation(float degrees) override;

		virtual void move(sf::Vector2f offset) override;
		virtual void rotate(float degrees) override;

		void display(const std::string& name); // selects the selected collection item for rendering
		void diplayAll() { m_currentGUIObject = nullptr; }

		GUIObject& getCurrentDisplayObject() { return *m_currentGUIObject; }

		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		GUIObject* m_currentGUIObject;
	};
}

#endif // _GUI_HPP_