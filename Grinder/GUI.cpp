#include "GUI.hpp"

namespace EngineComponents
{

	GUI::GUI(const std::string& backgroundPath, const std::string& name, size_t capacity) : GUIObject(backgroundPath, name), m_currentGUIObject{ nullptr }
	{
		getContainer().reserve(capacity);
	}

	void GUI::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{
		if (m_currentGUIObject != nullptr)
		{
			m_currentGUIObject->catchMouseEvent(event, mousePos);
			return;
		}
		offend([&](GUIObject* element) {element->catchMouseEvent(event, mousePos); });
	}

	void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		if (m_currentGUIObject != nullptr)
		{
			target.draw(*m_currentGUIObject, states);
			return;
		}
		std::for_each(getContainer().begin(), getContainer().end(), [&](GUIObject* element) {target.draw(*element, states); });
	}

	void GUI::setSize(const sf::Vector2f& targetSize)
	{
		offend([&](EngineComponents::GUIObject* object) {object->setSize(targetSize); });
	}

	void GUI::setScale(const sf::Vector2f factors)
	{
		offend([&](EngineComponents::GUIObject* object) {object->setScale(factors); });
	}

	void GUI::setPosition(sf::Vector2f pos)
	{
		offend([&](EngineComponents::GUIObject* object) {object->setPosition(pos); });
	}

	void GUI::setRotation(float degrees)
	{
		offend([&](EngineComponents::GUIObject* object) {object->setRotation(degrees); });
	}

	void GUI::move(sf::Vector2f offset)
	{
		offend([&](EngineComponents::GUIObject* object) {object->move(offset); });
	}

	void GUI::rotate(float degrees)
	{
		offend([&](EngineComponents::GUIObject* object) {object->rotate(degrees); });
	}

	void GUI::display(const std::string& name)
	{
		std::vector<GUIObject*>::iterator object = std::find_if(getContainer().begin(), getContainer().end(), [&](GUIObject* element)->bool {return (element->getName() == name); });
		if (object != getContainer().end())
			m_currentGUIObject = *object;
	}

}