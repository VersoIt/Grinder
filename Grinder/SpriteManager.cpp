#include "SpriteManager.hpp"

namespace EngineComponents
{
	SpriteManager::SpriteManager(const std::string& path, const sf::Vector2f& pos) : m_filePath{ path }
	{
		setTexture(path);
		if (path != "")
			m_sprite.setPosition(pos);
	}

	void SpriteManager::setTexture(const std::string& path)
	{
		if (path != "")
		{
			if (!m_texture.loadFromFile(path))
				throw EngineComponents::FileMissing("The texture file is missing.");

			m_filePath = path;

			m_sprite.setTexture(m_texture);
			m_sprite.setOrigin(static_cast<float>(getTexture().getSize().x / 2), static_cast<float>(getTexture().getSize().y / 2));
		}
	}

}