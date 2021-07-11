#include "SpriteManager.hpp"

namespace EngineComponents
{
	SpriteManager::SpriteManager(const std::string& path) : m_filePath{ path }
	{
		if (path != "")
			setTexture(path);
	}

	void SpriteManager::setTexture(const std::string& path)
	{
		if (!m_texture.loadFromFile(path))
			throw EngineComponents::FileMissing("The texture file is missing.");

		m_filePath = path;

		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(getTexture().getSize().x / 2, getTexture().getSize().y / 2);
		m_sprite.setPosition(getTexture().getSize().x / 2, getTexture().getSize().y / 2);
	}

}