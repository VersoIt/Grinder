#pragma once
#ifndef _MAP_RENDERER_HPP_
#define _MAP_RENDERER_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <iostream>
#include <cctype>

namespace EngineComponents
{
	class RenderCell
	{
	public:
		RenderCell(float x, float y, float width, float height) : rect(x, y, width, height)
		{

		}

		int         GetPropertyInt(const std::string& name);
		float       GetPropertyFloat(const std::string& name);
		std::string GetPropertyString(const std::string& name);

		std::string name;
		std::string type;
		std::map<std::string, std::string> properties;
		sf::FloatRect rect;
	};

	class TileMap : public sf::Drawable
	{
	public:
		TileMap() : m_texture{ nullptr }
		{
		}

		~TileMap();

		bool load(const std::string& tmx_file_path);

		RenderCell               getRenderCell(const std::string& name);
		std::vector<RenderCell>  getRenderCellsByName(const std::string& name);
		std::vector<RenderCell>  getRenderCellsByType(const std::string& type);
		std::vector<RenderCell>& getAllRenderCells();

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Texture* m_texture;
		std::vector<sf::VertexArray> m_tileLayers;
		std::vector<RenderCell>          m_objects;
	};
}

#endif // _MAP_RENDERER_HPP_