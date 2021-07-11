#include "RenderObject.hpp"

namespace EngineComponents
{

	RenderObject::RenderObject(const sf::Vector2f& increase, const std::string& backgroundPath, const std::string& text) : RenderObject(backgroundPath, text)
	{
		setScale(increase);
	}

	void RenderObject::setScale(const sf::Vector2f factors)
	{
		getSprite().setScale(factors); 
		getText().setScale(factors);
	}

	void RenderObject::setSize(const sf::Vector2f& targetSize)
	{
		getSprite().setScale(
			{
				targetSize.x / getSprite().getLocalBounds().width,
				targetSize.y / getSprite().getLocalBounds().height
			}
		);
		getText().setScale(
			{
				targetSize.x / getText().getLocalBounds().width,
				targetSize.y / getText().getLocalBounds().height
			}
		);
	}

	void RenderObject::setPosition(sf::Vector2f pos)
	{ 
		getSprite().setPosition(pos); 
		getText().setPosition(pos);
	}

	void RenderObject::setRotation(float degrees)
	{ 
		getSprite().setRotation(degrees); 
		getText().setRotation(degrees);
	}

	void RenderObject::move(sf::Vector2f offset)
	{ 
		getSprite().move(offset); 
		getText().move(offset);
	}

	void RenderObject::rotate(float degrees)
	{ 
		getSprite().rotate(degrees); 
		getText().rotate(degrees);
	}

	void RenderObject::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{ 
		SpriteManager::draw(target, states); 
		TextManager::draw(target,states);
	}

}