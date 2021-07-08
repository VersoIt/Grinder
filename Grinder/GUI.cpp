#include "GUI.hpp"

namespace EngineComponents
{

	GUI::GUI(const std::string& backgroundPath, size_t capacity) : GUIObject(backgroundPath)
	{
		getContainer().reserve(capacity);
	}

	void GUI::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{
		offend([&](GUIObject* element) {element->catchMouseEvent(event, mousePos); });
	}

	void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
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

}