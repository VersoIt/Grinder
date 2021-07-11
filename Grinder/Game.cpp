#include "Game.hpp"

namespace EngineComponents
{

	Game::Game(const std::string& mapPath)
	{
		if (!m_map.load(mapPath))
			throw EngineComponents::FileMissing("The map file is missing.");
	}
	void Game::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_map, states);
		std::for_each(m_entities.begin(), m_entities.end(), [&](Entity* entity) {target.draw(*entity, states); });
	}

	void Game::catchMouseEvent(const sf::Event & event, const sf::Vector2i & mousePos)
	{

	}

}