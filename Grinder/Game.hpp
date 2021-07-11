#pragma once
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"
#include "Entity.hpp"
#include "MapRenderer.hpp"
#include "GUI.hpp"

namespace EngineComponents
{
	class Game : public EngineComponents::GUI
	{
	public:
		Game(const std::string& mapPath);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		virtual void catchMouseEvent(const sf::Event& event, const sf::Vector2i& mousePos) override;
	private:
		std::vector<Entity*> m_entities;
		TileMap m_map;
	};
}

#endif // _GAME_HPP_