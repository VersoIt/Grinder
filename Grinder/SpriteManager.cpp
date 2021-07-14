#include "SpriteManager.hpp"

namespace EngineComponents
{
	SpriteManager::SpriteManager(const std::string& path, const sf::Vector2f& pos) : m_filePath{ path }
	{
		setTexture(path);
		if (path != "")
			sprite.setPosition(pos);
	}

	void SpriteManager::setTexture(const std::string& path)
	{
		if (path != "")
		{
			if (!texture.loadFromFile(path))
				throw EngineComponents::FileMissing("The texture file is missing.");

			m_filePath = path;

			sprite.setTexture(texture);
			sprite.setOrigin(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2));
		}
	}

	void SpriteManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_filePath != "")
			target.draw(sprite, states);
	}

}