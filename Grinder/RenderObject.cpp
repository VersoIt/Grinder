#include "RenderObject.hpp"

namespace EngineComponents
{
	void RenderObject::setSize(const sf::Vector2f& targetSize) 
	{
		getSprite().setScale(
			{
				targetSize.x / getSprite().getLocalBounds().width,
				targetSize.y / getSprite().getLocalBounds().height
			}
		);
	}

	void RenderObject::draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{ 
		SpriteManager::draw(target, states); 
		TextManager::draw(target,states);
	}

}