#include "GUI.hpp"

namespace EngineComponents
{

	GUI::GUI(const std::string& backgroundPath, const std::string& text, size_t capacity) : RenderObject(backgroundPath, text)
	{
		getContainer().reserve(capacity);
	}

	void GUI::catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos)
	{
		offend([&](RenderObject* element) {element->catchMouseEvent(event, mousePos); });
	}

	void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		std::for_each(getContainer().begin(), getContainer().end(), [&](RenderObject* element) {target.draw(*element, states); });
		TextManager::draw(target, states);
	}

	void GUI::setSize(const sf::Vector2f& targetSize)
	{
		getText().setScale(
			{
				targetSize.x / getSprite().getLocalBounds().width,
				targetSize.y / getSprite().getLocalBounds().height
			}
		);
		getSprite().setScale(
			{
				targetSize.x / getSprite().getLocalBounds().width,
				targetSize.y / getSprite().getLocalBounds().height
			}
		);
		offend([&](EngineComponents::RenderObject* object) {object->setSize(targetSize); });
	}

	void GUI::setScale(const sf::Vector2f factors)
	{
		getText().setScale(factors);
		getSprite().setScale(factors);
		offend([&](EngineComponents::RenderObject* object) {object->setScale(factors); });
	}

	void GUI::setPosition(sf::Vector2f pos)
	{
		getText().setPosition(pos);
		getSprite().setPosition(pos);
		offend([&](EngineComponents::RenderObject* object) {object->setPosition(pos); });
	}

	void GUI::setRotation(float degrees)
	{
		getText().setRotation(degrees);
		getSprite().setRotation(degrees);
		offend([&](EngineComponents::RenderObject* object) {object->setRotation(degrees); });
	}

	void GUI::move(sf::Vector2f offset)
	{
		getText().move(offset);
		getSprite().move(offset);
		offend([&](EngineComponents::RenderObject* object) {object->move(offset); });
	}

	void GUI::rotate(float degrees)
	{
		getText().rotate(degrees);
		getSprite().rotate(degrees);
		offend([&](EngineComponents::RenderObject* object) {object->rotate(degrees); });
	}

}