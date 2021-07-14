#include "EventObject.hpp"

namespace EngineComponents
{
	void EventObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		Object::draw(target, states);
	}

}