#pragma once
#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "Exceptions.hpp"

namespace EngineComponents
{
	struct SpriteManager : virtual public sf::Drawable
	{
		SpriteManager(const std::string& path, const sf::Vector2f& pos = { 0,0 });
		SpriteManager() {}

		void setTexture(const std::string& path);
		std::string getTextureFilePath() const { return m_filePath; }

		sf::Sprite sprite;
		sf::Texture texture;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		std::string m_filePath;

	};

}
#endif // _SPRITE_MANAGER_H_