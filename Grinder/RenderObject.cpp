#include "RenderObject.hpp"

namespace EngineComponents
{

	RenderObject::RenderObject(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text, const sf::Vector2f& pos) : RenderObject(backgroundPath, text, pos)
	{
		setScale(increase);
	}

	void RenderObject::setScale(const sf::Vector2f factors)
	{
		sprite.setScale(factors);
		text.setScale(factors);
	}

	void RenderObject::setSize(const sf::Vector2f& targetSize)
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

	void RenderObject::setPosition(const sf::Vector2f& pos)
	{
		sprite.setPosition(pos);
		text.setPosition(pos);
	}

	void RenderObject::setRotation(float degrees)
	{
		sprite.setRotation(degrees);
		text.setRotation(degrees);
	}

	void RenderObject::move(sf::Vector2f offset)
	{
		sprite.move(offset);
		text.move(offset);
	}

	void RenderObject::rotate(float degrees)
	{
		sprite.rotate(degrees);
		text.rotate(degrees);
	}

	void RenderObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		TextManager::draw(target, states);
	}

}