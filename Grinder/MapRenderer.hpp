#pragma once
#ifndef _MAP_RENDERER_HPP_
#define _MAP_RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <iostream>
#include <cctype>

namespace EngineComponents
{
	class RenderObject
	{
	public:
		RenderObject(float x, float y, float width, float height) : rect(x, y, width, height)
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
		~TileMap();

		bool load(const std::string& tmx_file_path);

		RenderObject               getRenderObject(const std::string& name);
		std::vector<RenderObject>  getRenderObjectsByName(const std::string& name);
		std::vector<RenderObject>  getRenderObjectsByType(const std::string& type);
		std::vector<RenderObject>& getAllRenderObjects();

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Texture* texture;
		std::vector<sf::VertexArray> tile_layers;
		std::vector<RenderObject>          objects;
	};
}

#endif // _MAP_RENDERER_HPP_