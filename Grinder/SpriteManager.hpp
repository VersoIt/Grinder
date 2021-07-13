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
	class SpriteManager : virtual public sf::Drawable
	{
	public:
		SpriteManager(const std::string& path, const sf::Vector2f& pos = { 0,0 });

		SpriteManager() {}

		void setTexture(const std::string& path);

		const sf::Sprite& getSprite() const { return m_sprite; }
		sf::Sprite& getSprite() { return m_sprite; }

		const sf::Texture& getTexture() const { return m_texture; }
		sf::Texture& getTexture() { return m_texture; }

		const std::string& getTextureFilePath() const { return m_filePath; }
		std::string& getTextureFilePath() { return m_filePath; }

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Sprite m_sprite;
		sf::Texture m_texture;

		std::string m_filePath;
	};

}
#endif // _SPRITE_MANAGER_H_