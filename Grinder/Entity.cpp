#include "Entity.hpp"

namespace EngineComponents
{
	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		SpriteManager::draw(target, states);
		TextManager::draw(target, states);
	}
}