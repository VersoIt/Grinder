#include "Object.hpp"

namespace EngineComponents
{

	Object::Object(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text, const sf::Vector2f& pos) : Object(backgroundPath, text, pos)
	{
		setScale(increase);
	}

	Object::Object(const std::string& backgroundPath, const std::string& text, const sf::Vector2f& pos) : SpriteManager(backgroundPath, pos), TextManager(text, pos)
	{
	}

	Object::Object(const std::string& backgroundPath, const sf::Text& text) : SpriteManager(backgroundPath), TextManager(text)
	{
	}

	Object::Object(const std::string& backgroundPath, const EngineComponents::TextManager& text) : SpriteManager(backgroundPath), TextManager(text)
	{
	}

	void Object::setScale(const sf::Vector2f factors)
	{
		sprite.setScale(factors);
		text.setScale(factors);
	}

	void Object::setSize(const sf::Vector2f& targetSize)
	{
		sprite.setScale(
			{
				targetSize.x / sprite.getLocalBounds().width,
				targetSize.y / sprite.getLocalBounds().height
			}
		);
		text.setScale(
			{
				targetSize.x / text.getLocalBounds().width,
				targetSize.y / text.getLocalBounds().height
			}
		);
	}

	void Object::setPosition(const sf::Vector2f& pos)
	{
		sprite.setPosition(pos);
		text.setPosition(pos);
	}

	void Object::setRotation(float degrees)
	{
		sprite.setRotation(degrees);
		text.setRotation(degrees);
	}

	void Object::move(sf::Vector2f offset)
	{
		sprite.move(offset);
		text.move(offset);
	}

	void Object::rotate(float degrees)
	{
		sprite.rotate(degrees);
		text.rotate(degrees);
	}

	void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		TextManager::draw(target, states);
	}
}