#include "GUIObject.hpp"

namespace EngineComponents
{
	void GUIObject::setSize(const sf::Vector2f& targetSize) 
	{
		getSprite().setScale(
			{
				targetSize.x / getSprite().getLocalBounds().width,
				targetSize.y / getSprite().getLocalBounds().height
			}
		);
	}
}