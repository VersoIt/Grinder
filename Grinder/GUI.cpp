#include "GUI.hpp"

namespace EngineComponents
{

	GUI::GUI(const std::string& backgroundPath, const std::string& text, size_t capacity) : EventObject(backgroundPath, text)
	{
		getContainer().reserve(capacity);
		sprite.setPosition(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2));
	}

	void GUI::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{
		offend([&](Object* element) 
			{
				EventObject* eventObject = dynamic_cast<EventObject*>(element);
				if (eventObject)
					eventObject->catchMouseEvent(event, mousePos); 
			}
		);
	}

	void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		std::for_each(getContainer().begin(), getContainer().end(), [&](Object* element) {target.draw(*element, states); });
		TextManager::draw(target, states);
	}

	void GUI::setSize(const sf::Vector2f& targetSize)
	{
		text.setScale(
			{
				targetSize.x / sprite.getLocalBounds().width,
				targetSize.y / sprite.getLocalBounds().height
			}
		);
		sprite.setScale(
			{
				targetSize.x / sprite.getLocalBounds().width,
				targetSize.y / sprite.getLocalBounds().height
			}
		);
		offend([&](EngineComponents::Object* object) {object->setSize(targetSize); });
	}

	void GUI::setScale(const sf::Vector2f factors)
	{
		text.setScale(factors);
		sprite.setScale(factors);
		offend([&](EngineComponents::Object* object) {object->setScale(factors); });
	}

	void GUI::setPosition(const sf::Vector2f& pos)
	{
		text.move(pos - sprite.getPosition());
		offend([&](EngineComponents::Object* object) {object->move(pos - sprite.getPosition()); });
		sprite.setPosition(pos);
	}

	void GUI::setRotation(float degrees)
	{
		text.setRotation(degrees);
		sprite.setRotation(degrees);
		offend([&](EngineComponents::Object* object) {object->setRotation(degrees); });
	}

	void GUI::move(sf::Vector2f offset)
	{
		text.move(offset);
		sprite.move(offset);
		offend([&](EngineComponents::Object* object) {object->move(offset); });
	}

	void GUI::rotate(float degrees)
	{
		text.rotate(degrees);
		sprite.rotate(degrees);
		offend([&](EngineComponents::Object* object) {object->rotate(degrees); });
	}

}